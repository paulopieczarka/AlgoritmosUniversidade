const ClonAlg = require("./ClonAlg");

class Main
{
    constructor()
    {
        this.clonAlg = new ClonAlg();
    }

    run()
    {
        this.clonAlg.run();
    }
}

const main = new Main();
main.run();