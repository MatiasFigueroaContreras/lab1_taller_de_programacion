#include "MinHeap.h"

int main()
{
	Rubik *r = new Rubik();

	r->print();
	Rubik *t = r->rotate(-1, 'U');
	t->print();

	State *state10 = new State(r, nullptr, 0, 'U', 1);
	MinHeap *heap = new MinHeap(5);
	heap->insert(10, state10);

	State *state15 = new State(r->rotate(-1, 'U'), state10, 1, 'U', -1);
	heap->insert(15, state15);

	State *state8 = new State(r->rotate(1, 'L'), state10, 1, 'L', -1);
	heap->insert(8, state8);
	heap->print();

	State *minState = heap->pull();
	heap->print();
	minState->cube->print();
	heap->pull();
	heap->print();

	heap->pull();
	heap->print();
}
