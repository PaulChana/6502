const process = require('process');

let startTime = 0;
const start = () => {
  startTime = process.hrtime.bigint();
};

const stop = () => {
  console.log(
    `Runtime was ${
      Number(process.hrtime.bigint() - startTime) / 1000000000
    } seconds`
  );
};

module.exports = {
  start,
  stop,
};
