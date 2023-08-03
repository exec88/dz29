#include <mutex>

struct Node
{
    int value;
    Node* next;
    std::mutex* node_mutex;
    Node(int value) : value(value), next(nullptr), node_mutex(nullptr) {}
};

class FineGrainedQueue
{
    Node* head;
    std::mutex* queue_mutex;
public:
    void insertIntoMiddle(int value, int position);
};

void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    Node* newNode = new Node(value);  // создаем новый узел

    int currPos = 0;

    queue_mutex->lock();    // блокируем весь список для поиска узла, за которым нужно вставить новый узел

    Node* current = head;

    while (currPos < pos - 1 && current->next != nullptr)     // в цикле идем по списку пока список не кончится
    {
        current = current->next;
        currPos++;
    }
    current->node_mutex->lock();    // нашли нужный узел за которым нужно вставить новый узел и блокируем найденный узел
    queue_mutex->unlock();          // разблокируем список

    Node* next = current->next;     // меняем указатель на следующий узел
                               
    current->next = newNode;
    newNode->next = next;           // связываем список обратно меняем указатель на узел, следующий после нового узла
    current->node_mutex->unlock();  // разблокируем текущий узел.
}