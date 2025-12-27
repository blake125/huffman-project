#include "../include/HuffmanCoder.h"
#include <benchmark/benchmark.h>

static void BM_FileEncode(benchmark::State& state) {
	for(auto _ : state) {
		HuffmanCoder coder;
		coder.encode("../../on_war.txt");
	}
}	

BENCHMARK(BM_FileEncode);

static void BM_FileDecode(benchmark::State& state) {
	for(auto _ : state) {
		HuffmanCoder coder;
		coder.decode("../../on_war.txt.huff");
	}
}	

BENCHMARK(BM_FileDecode);

BENCHMARK_MAIN();
