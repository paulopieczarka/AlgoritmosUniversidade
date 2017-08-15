
const HAND = {
    ROCK: 0,
    PAPER: 1,
    SCISSORS: 2
};

exports.didIWon = function(myHand, otherHand)
{
    if(myHand === otherHand){
        return "draw.";
    }

    if(myHand === HAND.ROCK && otherHand === HAND.SCISSORS){
        return "rock beats scissors.";
    }

    if(myHand === HAND.SCISSORS && otherHand === HAND.PAPER){
        return "scissors beats paper.";
    }

    if(myHand === HAND.PAPER && otherHand === HAND.ROCK){
        return "paper beats rock.";
    }

    return "i lose, it causes me great sadness."
}

exports.chooseRandom = function(){
    return Math.floor(Math.random()*3);
};