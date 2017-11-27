const Config = n => { return {
    MAX_LENGTH: n,
    PARTICLE_COUNT: 40,	
    V_MAX: 4, /* 4 8 12 16 20 */
    MAX_EPOCHS: 5000, /* 1000 5000 10000 50000 100000*/
    TARGET: 0,
    SHUFFLE_RANGE_MIN: 8,
    SHUFFLE_RANGE_MAX: 20
} };

module.exports = { Config };