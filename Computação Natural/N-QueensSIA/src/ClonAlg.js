const _ = require("underscore");
const { Antibody, Board } = require("./Chess");

class ClonAlg
{
    constructor()
    {
        this.paramN = 100;
        this.paramD = 10;
        this.paramB = 1;
        this.iterations = 1000;

        this.population = null;
        this.clonedPopulation = null;
        this.clonedPopulationRanks = null;
        this.clonedPopulationSize = null;
    }

    init()
    {
        this.population = Array(this.paramN);

        this.clonedPopulationSize = 0;
        for(let i=1; i <= this.paramN; i++) {
            this.clonedPopulationSize += parseInt(`${(((this.paramB*this.paramN)/i) + .5)}`); 
        }

        console.log("Cloned Population Size: ", this.clonedPopulationSize);

        this.clonedPopulation = Array(this.clonedPopulationSize);
        this.clonedPopulationRanks = Array(this.clonedPopulationSize);

        let initialAntibody = new Antibody(Array(8).fill(0).map((v,i) => i));
        this.population[0] = initialAntibody;

        console.log(initialAntibody);

        for(let i=1; i < this.paramN; i++)
        {
            this.population[i] = initialAntibody.clone();
            this.population[i].randomizeAll();
        }
    }

    calcPopulationFitness(population) {
        population.forEach( ind => ind.calcFitness() );
    }

    cloning()
    {
        this.population = this.population.sort((a, b) => b.getFitness() - a.getFitness());

        let index = 0;
        for(let rank = 1; rank <= this.population.length; rank++)
        {
            let copies = parseInt(`${(((this.paramB*this.paramN)/rank) + .5)}`);
            for(let copy = 0; copy < copies; copy++)
            {
                this.clonedPopulation[index] = this.population[rank-1].clone();
                this.clonedPopulationRanks[index] = rank;
                index++;
            }
        }
    }

    select()
    {
        this.clonedPopulation = this.clonedPopulation.sort((a, b) => b.getFitness() - a.getFitness());
        for(let i = 0; i < this.population.length; i++) {
            this.population[i] = this.clonedPopulation[i];
        }
    }

    birthAndReplace()
    {
        let offset = this.population.length - this.paramD;
        for(let i=0; i < this.paramD; i++) {
            this.population[offset+i].randomizeAll();
        }
    }

    hyperMutation() {
        for(let i=1; i < this.population.length; i++) {
            this.population[i].hyperMutate(_.random(0,2));
        }
    }

    run()
    {
        let iter = 0;
        this.init();

        while( iter++ < this.iterations )
        {
            this.calcPopulationFitness( this.population );
            this.cloning();
            this.hyperMutation();
            this.calcPopulationFitness( this.clonedPopulation );
            this.select();
            this.birthAndReplace();

            console.log(" #", iter, " fitness=", this.population[0].getFitness());

            if(this.population[0].getFitness() === 28) {
                break;
            }
        }

        const board = new Board(8);
        board.update(this.population[0]);
        board.print();
    }
}

module.exports = ClonAlg;