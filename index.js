const test = require('./build/Release/testaddon.node');

console.log(test.hello());


console.log('test.add(1,2)', test.add(1,2));
console.log('test.add(2,2)', test.add(2,2));
console.log('test.add(3,2)', test.add(3,2));
console.log('test.add(4,2)', test.add(4,2));
console.log('test.add(5,2)', test.add(5,2));