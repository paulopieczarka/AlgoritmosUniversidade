const { Particle } = require("./Particle");
const _ = require("underscore");

class ParticleSwarmOptimization
{
    constructor(config)
    {
        console.log("#### CREATING Particle Swarm Optimization ####");
        console.log(config);

        this.config = config;
        this.particleList = [];
        this.solutionList = [];
        this.epoch = 0;
    }

    exec()
    {
        // Initialize particles.
        this.particleList = [];
        this.solutionList = [];
        this.epoch = 0;

        let done = false;
        let aParticle = null;

        this.initializeParticles();

        while(!done)
        {
            if(this.epoch < this.config.MAX_EPOCHS)
            {
                console.log(`EPOCH #${this.epoch}`);

                // Calc conflicts for each particle.
                for(let i=0; i < this.config.PARTICLE_COUNT; i++)
                {
                    aParticle = this.particleList[i];
                    aParticle.calcConflicts();
                    if(aParticle.clashes === this.config.TARGET) {
                        done = true;
                    }
                }

                // Sorting particles.
                this.particleList = this.particleList.sort((a, b) => a.clashes - b.clashes);

                // Calculates the velocity of each particle.
                let worstResults = this.particleList[this.particleList.length - 1].clashes;

                this.particleList.forEach(p => {
                    let newVelocity = (this.config.V_MAX * p.clashes) / worstResults;
                    p.velocity = (newVelocity >= this.config.V_MAX) ? this.config.V_MAX : (newVelocity < 0) ? 0 : newVelocity;
                });

                // Move particles.
                this.updateParticles();

                this.epoch++;
            }
            else {
                done = true;
            }
        }

        // If epoch is max.
        if(this.epoch === this.config.MAX_EPOCHS)
        {
            console.log("No solution found. :(");
            return;
        }

        // Print all solutions.
        this.particleList.forEach(p => {
            if(p.clashes === this.config.TARGET) {
                p.printBoard();
                console.log("");
            }
        });
    }

    /**
     * Initializes all of the particles' placement of queens in ramdom positions.
     */
    initializeParticles()
    {
        // Create particle list.
        this.particleList = Array(this.config.PARTICLE_COUNT).fill(0).map(
            x => new Particle(this.config.MAX_LENGTH)
        );

        // Shuffle new particles.
        this.particleList.forEach((p, index) => {
            let shuffles = _.random(this.config.SHUFFLE_RANGE_MIN, this.config.SHUFFLE_RANGE_MAX);
            for(let i=0; i < shuffles; i++) {
                this.randSwapQueenPosition(index);
            }

            // Calculate particle conflicts.
            p.calcConflicts();
        });
    }

    /**
     * Updates each partilce according to its velocity.
     */
    updateParticles()
    {
        for(let i=1; i < this.config.PARTICLE_COUNT; i++)
        {
            let src = this.particleList[i-1];
            let dst = this.particleList[i];
            let numChanges = Math.floor( Math.abs( dst.velocity ) );

            for(let j=0; j < numChanges; j++)
            {
                if(Math.random() < .5){
                    this.randSwapQueenPosition(i);
                }

                this.moveParticle(src, dst);
            }
        }
    }

    /**
     * Particle movement. Moves the data of the destination particle closer to the best particle.
     * @param {Particle} best - particle better standing in the sorted population
     * @param {Particle} dst - current particle
     */
    moveParticle(best, dst)
    {
        let targetA = this.getRandNumber(this.config.PARTICLE_COUNT - 1);
        let targetB = 0;

        // targetB will be source's neighbor immediately succeeding targetA (circular).
        for(let i=0; i < this.config.MAX_LENGTH; i++)
        {
            if(best.sequence[i] === targetA)
            {
                let index = (i === this.config.MAX_LENGTH-1) ? 0 : i+1;
                targetB = best.sequence[index];
                break;
            }
        }

        // Move targetB next to targetA by switching values.
        let indexA = 0; let indexB = 0;

        for(let i=0; i < this.config.MAX_LENGTH; i++)
        {
            if(dst.sequence[i] === targetA) {
                indexA = i;
            }

            if(dst.sequence[i] === targetB) {
                indexB = i;
            }
        }

        // Switch indexB value with tempIndex value.
        let tempIndex = (indexA === this.config.MAX_LENGTH-1) ? 0 : indexA + 1;
        let temp = dst.sequence[tempIndex];
        dst.sequence[tempIndex] = dst.sequence[indexB];
        dst.sequence[indexB] = temp;
    }

    /**
     * Changes a position of the queens in a particle by swapping a randomly selected position.
     * @param {int} index of the particle
     */
    randSwapQueenPosition(index)
    {
        let pos0 = this.getRandNumber(this.config.MAX_LENGTH - 1);
        let pos1 = this.getRandNumber(this.config.MAX_LENGTH - 1, pos0);
        let sequenceValue = this.particleList[index].sequence[pos0];
        this.particleList[index].sequence[pos0] = this.particleList[index].sequence[pos1];
        this.particleList[index].sequence[pos1] = sequenceValue; 
    }

    /**
     * Random number generator.
     * @param {int} max 0 to max
     * @param {int} except this number.
     */
    getRandNumber(max, except = null)
    {
        let num = _.random(0, max);

        if(except && num === except){
            return this.getRandNumber(max, except);
        }

        return num;
    }
}

module.exports = { ParticleSwarmOptimization };