#include<iostream>
#include <fstream>
#include <chrono>
#include <string>

struct array1
{
public:
    int* arr = nullptr;
    int size = 0;

    void push_back(int elem) {
        arr = (int*)std::realloc(arr, (++size) * sizeof(int));
        arr[size - 1] = elem;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
    }

    void clean() {
        std::free(arr);
    }
};

struct array2 {
public:
    int* arr = nullptr;
    int size = 0;
    int max_size = 0;

    array2(int max_size) {
        size = 0;
        arr = nullptr;
        arr = (int*)std::realloc(arr, max_size * sizeof(int));
        this->max_size = max_size;
    }

    void push_back(int elem) {
        if (size == max_size) {
            arr = (int*)std::realloc(arr, (max_size+100) * sizeof(int));
            max_size =  (max_size+100);
        }
        arr[size++] = elem;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
    }

    void clean() {
        std::free(arr);
    }
};


struct array3 {
public:
    int* arr = nullptr;
    int size = 0;
    int max_size = 0;

    void push_back(int elem) {
        if (size < max_size) {
            arr[size++] = elem;
        }
        else if (size == 0) {
            arr = (int*)std::realloc(arr, sizeof(int));
            arr[size++] = elem;
            max_size = size;
        }
        else {
            max_size = size * 2;
            arr = (int*)std::realloc(arr, (max_size) * sizeof(int));
            arr[size++] = elem;
        }
    }
    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
    }

    void clean() {
        std::free(arr);
    }
};

struct queue {
    std::size_t poll_idx = 0;
    std::size_t push_idx = 0;
    int* data = new int;
    std::size_t size = 0;
    std::size_t max_size = 1;

    queue() {}

    queue(int size) {
        this->size = size;
        max_size = size;
        data = (int*)std::realloc(data, (max_size) * sizeof(int));
        push_idx = 0;
        poll_idx = max_size - 1;
        for (int i = 0; i < size; i++) {
            data[i] = i;
        }
    }

    std::pair<bool, int> poll() {
        if (size == 0) {
            return { false, 0 };
        }
        int elem = data[poll_idx];
        size--;
        if (poll_idx == push_idx) {
            ;
        }
        else if (poll_idx == 0) {
            poll_idx = max_size - 1;
        }
        else {
            poll_idx--;
        }
        return { true, elem };
    }

    void push(int elem) {
        if (size == 0) {
            data[push_idx] = elem;
            size++;
            return;
        }
        if (size == max_size) {
            data = (int*)std::realloc(data, (2 * max_size) * sizeof(int));
            std::size_t idx = 2 * max_size - 1;


            if (poll_idx >= push_idx) {
                for (std::size_t i = poll_idx; i >= push_idx; i--, idx--) {
                    data[idx] = data[i];
                    if (i == 0) {
                        idx--;
                        break;
                    }
                }
            }
            else {
                for (std::size_t i = poll_idx; i >= 0; i--, idx--) {
                    data[idx] = data[i];
                    if (i == 0) {
                        idx--;
                        break;
                    }
                }
                for (std::size_t i = max_size - 1; i >= push_idx; i--, idx--) {
                    data[idx] = data[i];
                    if (i == push_idx) {
                        idx--;
                        break;
                    }
                }
            }

            push_idx = max_size;
            poll_idx = 2 * max_size - 1;
            max_size *= 2;
        }

        if (push_idx == 0) {
            push_idx = max_size - 1;
            data[push_idx] = elem;
            size++;
        }
        else {
            data[--push_idx] = elem;
            size++;
        }
    }

    void del() {
        std::free(data);
    }



    void print() {
        if (size != 0) {
            if (poll_idx >= push_idx) {
                for (std::size_t i = push_idx; i <= poll_idx; ++i) {
                    std::cout << data[i] << ' ';
                }
            }
            else {
                for (std::size_t i = push_idx; i < max_size; ++i) {
                    std::cout << data[i] << ' ';
                }
                std::cout << ": ";
                for (std::size_t i = 0; i <= poll_idx; ++i) {
                    std::cout << data[i] << ' ';
                }
            }

        }

        std::cout << std::endl << "size = " << size << " maxsize = " << max_size << std::endl;
        std::cout << "poll_idx = " << poll_idx << " push_idx = " << push_idx << std::endl;
    }

};


void test_queue() {
    queue* q = new queue();
    q->print();
    while (true) {
        char elem;
        std::cin >> elem;
        if (elem == 'a') {
            int key;
            std::cin >> key;
            q->push(key);
            q->print();
        }
        else if (elem == 'd') {
            auto p = q->poll();
            std::cout << "Return " << p.first << ' ' << p.second << std::endl;;
            q->print();
        }
    }
}


void count_time_array1() {
    for (int n = 10; n < 20000; n += 250) {
        auto begin = std::chrono::steady_clock::now();
        const int MAX_ITER = 1000;
        for (int iter = 0; iter < MAX_ITER; iter++) {
            array1* arr = new array1;
            for (int i = 0; i < n; ++i) {
                arr->push_back(i);
            }
            arr->clean();
        }
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout <<  time_span.count()<< " " ;
    }
    std::cout<<std::endl;
    for (int n = 10; n < 20000; n += 250) {
        std::cout<<n<<" ";
    }
    std::cout << "end" << std::endl;
}

void count_time_array2() {

    for (int n = 10; n < 100000; n += 500) {
        auto begin = std::chrono::steady_clock::now();
        const int MAX_ITER = 500;
        for (int iter = 0; iter < MAX_ITER; iter++) {
            array2* arr = new array2(0);
            for (int i = 0; i < n; ++i) {
                arr->push_back(i);
            }
            arr->clean();
        }
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout << time_span.count()<<" ";
    }
    std::cout<<std::endl;
    for (int n = 10; n < 100000; n += 500) {
        std::cout<<n<<" ";
    }

    std::cout << "end" << std::endl;
}


void count_time_array3() {


    for (int n = 10; n < 100000; n += 500) {
        auto begin = std::chrono::steady_clock::now();
        const int MAX_ITER = 10000;
        for (int iter = 0; iter < MAX_ITER; iter++) {
            array3* arr = new array3;
            for (int i = 0; i < n; ++i) {
                arr->push_back(i);
            }
            arr->clean();
        }
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout  << time_span.count() << " ";
    }
    std::cout<<std::endl;
    for (int n = 10; n < 100000; n += 500) {
        std::cout<<n<<" ";
    }

    std::cout << "end" << std::endl;
}

void count_time_queue_push() {
        for (int n = 10; n < 50000; n += 500) {
            auto begin = std::chrono::steady_clock::now();
            const int MAX_ITER = 10000;
            for (int i = 0; i < MAX_ITER; i++){
                queue* q = new queue();
                for (int i = 0; i < n; i++) {
                    q->push(i);
                }
                q->del();
                delete q;
            }

            auto end = std::chrono::steady_clock::now();
            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            std::cout << time_span.count() << " ";
        }
std::cout<<std::endl;
    for (int n = 10; n < 50000; n += 500) {
        std::cout<<n<<" ";
    }

    std::cout << "end" << std::endl;
}

void count_time_queue_poll() {
        for (int n = 10; n < 50000; n += 500) {
            auto begin = std::chrono::steady_clock::now();
            const int MAX_ITER = 10000;
            for (int i = 0; i < MAX_ITER; i++) {
                queue* q = new queue(n);
                for (int i = 0; i < n; i++) {
                    q->poll();
                }
                q->del();
                delete q;
            }

            auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout << time_span.count() << " ";
    }
    std::cout<<std::endl;
    for (int n = 10; n < 50000; n += 500) {
        std::cout<<n<<" ";
    }
    std::cout << "end" << std::endl;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    test_queue();
    return 0;
}
