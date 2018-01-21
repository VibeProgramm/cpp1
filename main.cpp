#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>

#if 0
std::condition_variable foo;
std::mutex mtx;
void secondThread()
{
	while (true)
	{
		foo.wait(std::unique_lock<std::mutex>(mtx));
		std::cout << " ----------------------------" << std::endl;
		std::cout << "|processing a notification...|" << std::endl;
		std::cout << " ----------------------------" << std::endl;
	}
}
int main()
{
	std::thread subThread = std::thread(&secondThread);
	int count = 0;
	while (true)
	{
		if (count % 10 == 0)
		{
			foo.notify_one();
		}
		std::cout << "Main thread working on gathering notifications..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		count++;
	}
	return 0;
}
#endif 


struct Renderer
{
	int x, y, z;

	void(*submit)(struct Renderer *self, int x, int y, int z);
	void(*flush)(struct Renderer *self);
};

void submit2d(Renderer* self, int x, int y, int z)
{
	self->x = x;
	self->y = y;
	self->z = z;

	printf("Submited data: %d, %d\n", x, y);
}

void flush2d(Renderer *self)
{
	printf("Flushing 2d renderable at coordinates: %d, %d\n", self->x, self->y);
}

void flushInit2d(Renderer* self)
{
	self->flush = flush2d;
}

void submitInit2d(Renderer* self)
{
	self->submit = submit2d;
}


void submit3d(Renderer* self, int x, int y, int z)
{
	self->x = x;
	self->y = y;
	self->z = z;

	printf("Submited data: %d, %d, %d\n", x, y, z);
}

void flush3d(Renderer *self)
{
	printf("Flushing 3d renderable at coordinates: %d, %d, %d\n", self->x, self->y, self->z);
}

void flushInit3d(Renderer* self)
{
	self->flush = flush3d;
}

void submitInit3d(Renderer* self)
{
	self->submit = submit3d;
}



int main()
{
	Renderer renderer2d, renderer3d;

	submitInit2d(&renderer2d);
	flushInit2d(&renderer2d);

	submitInit3d(&renderer3d);
	flushInit3d(&renderer3d);

	renderer2d.submit(&renderer2d, 10, 20, 0);
	renderer2d.flush(&renderer2d);
	printf("\n");
	renderer3d.submit(&renderer3d, 15, 30, 5);
	renderer3d.flush(&renderer3d);

	system("PAUSE");
	return 0;
}