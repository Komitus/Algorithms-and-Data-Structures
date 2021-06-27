#include "priority_queue.hpp"

PriorityQueue::PriorityQueue() {}

PriorityQueue::~PriorityQueue() {
    queue.clear();
    queue.shrink_to_fit();
}

std::vector<std::shared_ptr<Element>> PriorityQueue::get_queue(){
    return this->queue;
}
uint32_t PriorityQueue::heap_parent(uint32_t i) {
    return (i + 1) / 2 - 1;
}

uint32_t PriorityQueue::left(uint32_t i) {
    return 2 * (i + 1) - 1;
}

uint32_t PriorityQueue::right(uint32_t i) {
    return 2 * (i + 1);
}

bool PriorityQueue::empty() {
    if (heap_size == 0) {
        return true;
    } else {
        return false;
    }
}

void PriorityQueue::top () {
    if (heap_size > 0) {
        std::cout << queue.at(0)->key << std::endl;
    } else {
        std::cout << "\n";
    }
}

uint32_t PriorityQueue::pop() {
    compares++;
    if (heap_size < 1) {
        return 0;
    }

    uint32_t first_elem = queue.at(0)->key;
    queue.at(0) = queue.at(heap_size - 1);
    heap_size--;
    heapify(0);

    return first_elem;
}

void PriorityQueue::heapify(uint32_t i) {
    uint32_t l = left(i);
    uint32_t r = right(i);
    uint32_t highest; //i mean smallest value but highest priority

    compares++;
    if (l < heap_size && queue.at(l)->dist < queue.at(i)->dist) {
        highest = l;
    } else {
        highest = i;
    }

    compares++;
    if (r < heap_size && queue.at(r)->dist < queue.at(highest)->dist) {
        highest = r;
    }

    compares++;
    if (highest != i) {
        std::swap(queue.at(i), queue.at(highest));
        heapify(highest);
    }
}

std::shared_ptr<Element> PriorityQueue::insert(uint32_t key, uint32_t *parent, double dist) {
    std::shared_ptr<Element> e = std::make_shared<Element> (key, parent, dist);
    heap_size++;
    queue.push_back(e);

    int i = heap_size - 1;
    compares++;
    while (i > 0 && queue.at(heap_parent(i))->dist > dist) {
        std::swap(queue.at(i), queue.at(heap_parent(i)));
        i = heap_parent(i);
        compares++;
    }

    return e;
}

void PriorityQueue::priority (uint32_t key, double dist) {
    for (uint32_t i = 0; i < heap_size; i++) {
        if (queue.at(i)->key == key) {
            compares++;
            if (queue.at(i)->dist < dist) {
                continue;
            }

            uint32_t j = i;
            queue.at(i)->dist = dist;

            compares++;
            while (j > 0 && queue.at(heap_parent(j))->dist > queue.at(j)->dist ) {
                std::swap (queue.at(j), queue.at(heap_parent(j)));
                j = heap_parent(j);
                compares++;
            }
        }
    }
}

std::shared_ptr<Element> PriorityQueue::find(uint32_t key) {
    for (uint32_t i = 0; i < heap_size; i++) {
        compares++;
        if (queue.at(i)->key == key) {
            return queue.at(i);
        }
    }
    return nullptr;
}

void PriorityQueue::print() {
    for (uint32_t i = 0; i < heap_size; i++) {
        std::cout << "(" << queue.at(i)->key << "," << queue.at(i)->dist << ") ";
    }
    std::cout << "\n";
}

uint32_t PriorityQueue::get_compares(){
    return this->compares;
}

void PriorityQueue::zero_compares(){
    this->compares = 0;
}

Element PriorityQueue::read_elem(uint32_t index){
    return *this->queue.at(index);
}