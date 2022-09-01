#include "HashTable.h"

int main(){
	HashTable *hash = new HashTable(15);
	Rubik *c = new Rubik();
	hash->add(c);
	Rubik *p = c->rotate(1, 'R');
	hash->add(p);
	Rubik *t = p->rotate(1, 'U');
	hash->add(t);

	std::cout << hash->isInTable(t) << std::endl;
}
