//
// Timer.cpp
//
// This sample demonstrates the Timer and Stopwatch classes.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Timer.h"
#include "Poco/Thread.h"
#include "Poco/Stopwatch.h"
#include "Poco/RegularExpression.h"
#include <iostream>


using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;
using Poco::Stopwatch;
using Poco::RegularExpression;


class TimerExample
{
public:
	TimerExample()
	{
		_sw.start();
	}

	void onTimer(Timer& timer)
	{
		std::cout << "Callback called after " << _sw.elapsed()/1000 << " milliseconds." << std::endl;
	}

private:
	Stopwatch _sw;
};

void testTimer()
{
	TimerExample example;

        Timer timer(25, 50);
        timer.start(TimerCallback<TimerExample>(example, &TimerExample::onTimer));

        Thread::sleep(500);

        timer.stop();
}

void testRegularExpression()
{
	Poco::RegularExpression regex("^(\\w+)(?:\\[(\\d+)\\])?\\.(\\w+)$",
							  Poco::RegularExpression::RE_CASELESS |
							  Poco::RegularExpression::RE_ANCHORED
							  );
	std::vector<std::string> splitOutput;
	const bool ok = regex.split("field[0].name", 0, splitOutput);
	if (!ok) {
		std::cerr << "`regex.split(\"field[0].name\", 0, splitOutput)` returned `false`, expected `true`)" << std::endl;
		exit(1);
	}
	if (splitOutput.size() != 4) {
		std::cerr << "expected `splitOutput.size() == 4`, but got " << splitOutput.size() << std::endl;
		exit(1);
	}
	if (splitOutput[0] != "field[0].name") {
		std::cerr << "expected `splitOutput[0] == \"field[0].name\", but got " << splitOutput[0] << std::endl;
		exit(1);
	}
	if (splitOutput[1] != "field") {
		std::cerr << "expected `splitOutput[1] == \"field\", but got " << splitOutput[1] << std::endl;
		exit(1);
	}
	if (splitOutput[2] != "0") {
		std::cerr << "expected `splitOutput[2] == \"0\", but got " << splitOutput[2] << std::endl;
		exit(1);
	}
	if (splitOutput[3] != "name") {
		std::cerr << "expected `splitOutput[3] == \"name\", but got " << splitOutput[3] << std::endl;
		exit(1);
	}
}



int main(int argc, char** argv)
{
	testTimer();
	testRegularExpression();
	return 0;
}
