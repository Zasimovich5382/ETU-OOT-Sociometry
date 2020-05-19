#include <iostream>
#include <string>
#include "ercontainer.h"
// #include "socialentity.h"
// REMOVE THIS FILE LATER
void print_relation(Relation<std::string>& r){
    std::cout << "{" << " ";
    std::cout << r.getFirstEntity()->getName();
    std::cout << " " <<r.getType() << " ";
    std::cout << r.getSecondEntity()->getName();
    std::cout << "}" << " ";
}

void print_entitity(SocialEntity<std::string>& e){
    std::cout <<'<'<< e.getName() << ", age: "<< e.getAge() << ", gender: " << e.getGender() << '>' << " ";
    for(auto& r : e.getRelations()){
        print_relation(r);
    }
    std::cout << std::endl;
}

void print_entititis(ERContainer<std::string>& graph){
    for(auto it = graph.begin(); it != graph.end(); it++){
        print_entitity(*it);
    }
    std::cout << std::endl;
}

int main(){
    ERContainer<std::string> graph;
    graph.addEntity("aaa", MALE);
    graph.addEntity("bbb", FEMALE);

    graph.addRelation("aaa", "bbb", POSITIVE);
    // graph.removeRelation("aaa", "bbb");

    graph.addEntity("ccc", MALE);
    graph.addRelation("aaa", "bbb", NEGATIVE); //doesn't add because relation already exists
    print_entititis(graph);

    auto e = graph.find("ccc");
    e->setAge(15);
    print_entititis(graph);

    graph.addRelation("bbb", "ccc", NEGATIVE);
    print_entititis(graph);

    graph.removeEntity("bbb");
    print_entititis(graph);

    graph.addRelation("aaa", "ccc", NEGATIVE);
    graph.editRelation("aaa", "ccc", POSITIVE);
    graph.addEntity("ttt", MALE);
    print_entititis(graph);
    graph.removeRelation("aaa", "ccc");
    print_entititis(graph);

    return 0;
}
