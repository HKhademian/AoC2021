#!/usr/bin/env -S deno run --allow-read

const parsePosition1 = (input: [string, number][]): [number, number] => {
  const result : [number, number] = [0, 0];
  for (const [command, value] of input) {
    if(command == 'up') result[1] -= value;
    else if ( command == 'down') result[1] += value;
    else if ( command == 'forward') result[0] += value;
  }
  return result;
};

const parsePosition2 = (input: [string, number][]): [number, number] => {
  let horizontal = 0;
  let depth = 0;
  let aim = 0;
  for (const [command, value] of input) {
    if(command == 'up') aim -= value;
    else if ( command == 'down') aim += value;
    else if ( command == 'forward') {
      horizontal += value;
      depth += aim * value;
    }
  }
  return [horizontal, depth];
};

const parseMap = (input: string): [string, number][] => {
  return input.split('\n').map(line => {
    let x = line.split(' ');
    return [x[0], parseInt(x[1])];
  });
};

const input = await Deno.readTextFile('./input.txt');

const result1 = parsePosition1(parseMap(input));
console.log('part1', result1, result1[0] * result1[1]);

const result2 = parsePosition2(parseMap(input));
console.log('part2', result2, result2[0] * result2[1]);

