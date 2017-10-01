
let WebSocket = require('ws');
let Game = require('./RockPaperScissors');
let ws = new WebSocket('ws://localhost:65300');

var myHand;

ws.on('open', () => {
    ws.send("do you wanna play?");
});

ws.on('message', msg => {
    console.log(msg);
    if(msg === 'yes.')
    {
        console.log("---------------------------------------- NEW GAME");
        myHand = Game.chooseRandom();
        ws.send("play:"+myHand);
    }
    else if(msg.startsWith("play:")) 
    {
        console.log(Game.didIWon(myHand, parseInt(msg.replace("play:", ""), 10)));
    }
});