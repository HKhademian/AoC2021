#!/usr/bin/env -S deno run 

const processIncrease = (depths: number[]):number => {
	return depths.reduce(([incr,lastDepth], depth) => {
		if(depth>lastDepth) return [incr+1, depth];
		else return [incr, depth];
	}, [0, depths[0]])[0];
};

const slidingWindow = (depths: number[]):number[] => {
	let x1: number, x2: number;
	return <number[]> depths.map(it => {
		let sum = (x1===undefined || x2===undefined) ? undefined :
			x1+x2+it;
		x1=x2;
		x2=it;
		return sum;
	})
	.filter(it => it!==undefined);
};

const inputs = await Deno.readTextFile("./input.txt");
const depths = inputs.split("\n").map(x => parseInt(x));
const depthSum = slidingWindow(depths);

console.log(processIncrease(depthSum));
