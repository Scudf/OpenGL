#pragma once

#include <memory>


struct PngTexData
{
	unsigned int width;
	unsigned int height;

	std::shared_ptr<char> data;

	bool alphaChannel;

	PngTexData()
		: width(0)
		, height(0)
		, data(0)
		, alphaChannel(false)
	{}
};

bool loadPng(const char* path, PngTexData& result);