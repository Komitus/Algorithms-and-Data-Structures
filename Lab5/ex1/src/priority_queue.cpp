#include "priority_queue.hpp"

priority_queue::priority_queue() {}

priority_queue::~priority_queue() {
    queue.clear();
    queue.shrink_to_fit();
}

uint32_t priority_queue::parent(uint32_t i) {
    return (i + 1) / 2 - 1;
}

uint32_t priority_queue::left(uint32_t i) {
    return 2 * (i + 1) - 1;
}

uint32_t priority_queue::right(uint32_t i) {
    return 2 * (i + 1);
}

void priority_queue::empty() {
    if (heap_size == 0) {
        std::cout << "1" << std::endl;
    } else {
        std::cout << "0" << std::endl;
    }
}

void priority_queue::top () {
    if (heap_size > 0) {
        std::cout << queue.at(0).key << std::endl;
    } else {
        std::cout << "\n";
    }
}

void priority_queue::pop() {
    compares++;
    if (heap_size < 1) {
        //std::cout << "\n";
        return;
    }

    element first_elem = queue.at(0);
    queue.at(0) = queue.at(heap_size - 1);
    heap_size--;
    heapify(0);

    //std::cout << first_elem.key << std::endl;
}

void priority_queue::heapify(uint32_t i) {
    uint32_t l = left(i);
    uint32_t r = right(i);
    uint32_t highest; //i mean smallest value but highest priority

    compares++;
    if (l < heap_size && queue.at(l).p < queue.at(i).p) {
        highest = l;
    } else {
        highest = i;
    }

    compares++;
    if (r < heap_size && queue.at(r).p < queue.at(highest).p) {
        highest = r;
    }

    compares++;
    if (highest != i) {
        std::swap(queue.at(i), queue.at(highest));
        heapify(highest);
    }
}

void priority_queue::insert(int key, uint32_t p) {
    element e = element (key, p);
    heap_size++;
    queue.push_back(e);

    uint32_t i = heap_size - 1;
    //heapify but in reversed oreder (from heap-end to root)
    compares++;
    while (i > 0 && queue.at(parent(i)).p > p) {
        std::swap(queue.at(i), queue.at(parent(i)));
        i = parent(i);
        compares++;
    }
}

void priority_queue::priority(int key, uint32_t p) {

    for (uint32_t i = 0; i < heap_size; i++) {
        //compares++;
        if (queue.at(i).key == key) {
            compares++;
            if (queue.at(i).p > p) {
                continue;
            }
          
            uint32_t j = i;
            queue.at(i).p = p;
            compares++;
            while (j > 0 && queue.at(parent(j)).p > queue.at(j).p) {
                std::swap(queue.at(j), queue.at(parent(j)));
                j = parent(j);
                compares++;
            }
        }
    }
}

void priority_queue::print() {
    for (uint32_t i = 0; i < heap_size; i++) {
        std::cout << "(" << queue.at(i).key << "," << queue.at(i).p << ") ";
    }
    std::cout << "\n";
}

uint32_t priority_queue::get_compares(){
    return this->compares;
}

void priority_queue::zero_compares(){
    this->compares = 0;
}

element priority_queue::read_elem(uint32_t index){
    element ret = this->queue.at(index);
    return ret;
}