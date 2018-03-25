
#ifndef DZ04_GRAPHNODE_H
#define DZ04_GRAPHNODE_H


class GraphNode {
private:
    int index;
public:
    enum {
        invalid_index = -1
    };

    explicit GraphNode(int index) : index(index) {}

    GraphNode() : index(invalid_index) {}

    int getIndex() const { return index; }

    void setIndex(int i) { index = i; }
};


#endif //DZ04_GRAPHNODE_H
