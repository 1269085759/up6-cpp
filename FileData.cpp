#include "stdafx.h"
#include "FileData.h"

FileData::FileData()
{
	this->uid = 0;
	this->lenLoc = this->lenSvr = 0;
	this->sizeLoc = "0byte";
	this->perSvr = "0%";
	this->complete = false;
	this->deleted = false;
	this->f_fdTask = false;
	this->f_fdChild = false;
}

FileData::~FileData()
{
}