/*
	Copyright (c) 2015-2016 Xavier Leclercq

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
	IN THE SOFTWARE.
*/

#include "TestTeardownAction.h"
#include <boost/filesystem/operations.hpp>

namespace Ishiko
{
namespace TestFramework
{

TestTeardownAction::TestTeardownAction()
{
}

TestTeardownAction::~TestTeardownAction()
{
}

void TestTeardownAction::run()
{
	// Default implementation does nothing
}

FilesTeardownAction::FilesTeardownAction()
{
}

FilesTeardownAction::~FilesTeardownAction()
{
}

void FilesTeardownAction::run()
{
	for (size_t i = 0; i < d_files.size(); ++i)
	{
		boost::filesystem::remove(d_files[i]);
	}
}

void FilesTeardownAction::add(const boost::filesystem::path& path)
{
	d_files.push_back(path);
}

DirectoriesTeardownAction::DirectoriesTeardownAction()
{
}

DirectoriesTeardownAction::~DirectoriesTeardownAction()
{
}

void DirectoriesTeardownAction::run()
{
	for (size_t i = 0; i < d_directories.size(); ++i)
	{
		boost::filesystem::remove(d_directories[i]);
	}
}

void DirectoriesTeardownAction::add(const boost::filesystem::path& path)
{
	d_directories.push_back(path);
}

}
}
