const _ = require("underscore");

class Particle
{
    constructor(n)
    {
        this.maxLength = n;
        this.sequence = Array(n).fill(0).map((x, i) => i);
        this.velocity = 0.0; // fitness.
        this.clashes = 0; // pBest.
    }

    calcConflicts()
    {
        let clashes = 0;
        let rowColClashes = Math.abs(this.sequence.length - _.unique(this.sequence).length);
        clashes += rowColClashes;

        //Diagonal clashes.
        for(let i=0; i < this.sequence.length; i++)
        {
            for(let j=0; j < this.sequence.length; j++)
            {
                if(i != j)
                {
                    let dx = Math.abs(i - j);
                    let dy = Math.abs(this.sequence[i] - this.sequence[j]);
                    if(dx === dy){
                        clashes++;
                    }
                }
            }
        }

        this.clashes = clashes;
    }

    printBoard()
    {
        let board = Array(this.maxLength).fill([]).map(
            x => Array(this.maxLength).fill(0)
        );

        this.sequence.forEach( (x, i) => board[i][this.sequence[i]] = 1 );
        console.log(board);
    }
}

module.exports = { Particle };