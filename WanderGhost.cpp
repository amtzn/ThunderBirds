#include "WanderGhost.h"

int WanderGhost::move()
{
	if (type == WanderType::Random) {
		int res;
		if (counter > 10) {
			setDirection((Direction)(rand() % 4));
		}
		res = Ghost::move();
		counter > 10 ? counter = 1 : counter += rand() % 4 + 1;
		return res;
	}
	else {
		return Ghost::move();
	}
}

