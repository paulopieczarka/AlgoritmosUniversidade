const { Config } = require("./Conf");
const { ParticleSwarmOptimization } = require("./ParticleSwarmOptimization");

class Main
{
    constructor()
    {
        this.pso = new ParticleSwarmOptimization(Config(8));
    }

    run()
    {
        console.log("\n#### RUNNING Particle Swarm Optimization ####");
        this.pso.exec();
    }
};

// Start the code.
let main = new Main();
main.run();