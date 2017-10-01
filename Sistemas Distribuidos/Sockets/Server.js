
let WebSocketServer = require('ws').Server;
let wsServer = new WebSocketServer({ port: 65300 });

let Game = require('./RockPaperScissors');
var myHand;

wsServer.on('connection', ws => {
    ws.on('message', msg => {
        console.log(msg);
        if(msg === "do you wanna play?")
        {
            ws.send("yes.");
        }
        else if(msg.startsWith("play:")) 
        {
            myHand = Game.chooseRandom();
            ws.send("play:"+myHand);

            console.log(Game.didIWon(myHand, parseInt(msg.replace("play:", ""), 10)));

            console.log("Game will start again in 2s.");
            setTimeout(() => { ws.send("yes.") }, 2000);
            console.log("---------------------------------------- NEW GAME");
        }
    });
});