#include "bst.h"
#include <string>


void test_template_comparison()
{
    bst<int,int,std::greater<int>> t1;
    std::pair<int,int> p;
    std::vector<int> v{4,2,6,1,3,5,7};
    for(long unsigned int j=0; j< v.size(); j++)
    {
        p = {v[j], v[j]};
        t1.insert(p);
    }
    std::cout << "\ninserted v={4,2,6,1,3,5,7} in t1" << std::endl;
    std::cout << t1 << std::endl;
};


int main() {

try 
    { 
        /* Int:Int couples */
        std::pair<const int, int> pair{4,4};
        std::pair<const int, int> pair2{2,2};
        std::pair<const int, int> pair3{6,6};
        std::pair<const int, int> pair4{1,1};
        std::pair<const int, int> pair5{5,5};
        std::pair<const int, int> pair6{3,3};
        std::pair<const int, int> pair7{7,2};
        std::pair<const int, int> pair8{4,7};
          
        bst<int,int> inttree{pair}; 
        inttree.insert(pair2); 
        inttree.insert(pair3);
        inttree.insert(pair4); 
        inttree.insert(pair5); 
        inttree.insert(pair6); 
        inttree.insert(pair7); 
        inttree.insert(pair8); 

        std::cout<<"************Test insert & constructor ************"<<std::endl;
        std::cout<<"The unbalanced int tree"<<std::endl;
        std::cout<<inttree<<std::endl;

        /* Char:int couples */
        std::pair<const char,int> p1{'a',1};    
        std::pair<const char,int> p2{'b',2};    
        std::pair<const char,int> p3{'c',3};    
        std::pair<const char,int> p4{'d',4};    
        std::pair<const char,int> p5{'e',5};    

        bst<char,int> chartree{p1}; 
        chartree.insert(p2); 
        chartree.insert(p3); 
        chartree.insert(p4);
        chartree.insert(p5);

        std::cout<<"The unbalanced char tree"<<std::endl;
        std::cout<<chartree<<std::endl;


        std::cout<<"************Test Copy Assignment************"<<std::endl;
        std::cout<<"---------I copy assign the char:int tree to generate a new one: --------- "<<std::endl;
        bst<char,int> alberochar=chartree;
        std::cout<<alberochar<<std::endl;

        std::cout<<"---------I create an empty tree and then fill it with the int:int tree: --------- "<<std::endl;
        bst<int,int> albero2int{};  
        albero2int=inttree;
        std::cout<<albero2int<<std::endl;



        std::cout<<"************Test balance************"<<std::endl;
        /* Test balance */
        chartree.balance();
        inttree.balance();

        std::cout<<"The unbalanced int tree"<<std::endl;
        std::cout<<inttree<<std::endl;

        std::cout<<"The unbalanced char tree"<<std::endl;
        std::cout<<chartree<<std::endl;


         /* Test find on both trees */
        std::cout<<"************Test find on both trees************"<<std::endl; 
        int No_key=11;
        (inttree.find(No_key)==inttree.end() ?\
        std::cout <<No_key<< "-> Not found" << std::endl :\
        std::cout <<No_key<< "-> Found" << std::endl);
        

        char key='a';
        (chartree.find(key)==chartree.end() ?\
        std::cout <<key<< "-> Not found" << std::endl :\
        std::cout <<key<< "-> Found" << std::endl);


         /* Test begin */
        std::cout<<"************Test begin ************"<<std::endl;


        std::cout<<"---------Int tree: --------- "<<std::endl;
        auto mybegin = inttree.begin();
        std::cout << "first key: " << mybegin->first << " first value: " << mybegin->second << "\n";

        auto cit = inttree.cbegin();
        ++cit;
        std::cout << "second key: " << cit->first << " second value: " << cit->second << "\n";

        std::cout<<"Char tree: "<<std::endl;

        std::cout<<"--------- Char tree: ---------"<<std::endl;
        auto mybegin1 = chartree.begin();
        std::cout << "first key: " << mybegin1->first << " first value: " << mybegin1->second << "\n";

        auto cit1 = chartree.cbegin();
        ++cit1;
        std::cout << "second key: " << cit1->first << " second value: " << cit1->second << "\n";

       
        
        /* Test Subscript */
        std::cout<<"************ Subscript operator************"<<std::endl;

        auto valore=inttree[No_key];
        (valore?\
        std::cout <<No_key<< "-> Has been found with value: " <<valore << std::endl :\
        std::cout <<No_key<< "-> Has been inserted with value " <<valore << std::endl);

        valore=chartree[key];
        (valore?\
        std::cout <<key<< "-> Has been found with value: " <<valore << std::endl :\
        std::cout <<key<< "-> Has been inserted with value " <<valore << std::endl);

      

        /* Test operator =  */
        std::cout<<"************ Test operator = ************"<<std::endl;

        std::cout<<"---------  Tree is : ---------"<<std::endl;
        std::cout<<inttree<<std::endl;

         std::cout<<"---------  I create Tree[1] from Tree : ---------"<<std::endl;
         auto inttree1{inttree};
         std::cout<<"---------  Tree[1] is : ---------"<<std::endl;
         std::cout<<inttree1<<std::endl;

        std::cout<<"---------  I create Tree[2] empty : ---------"<<std::endl;
        bst<int,int> inttree2{};
        std::cout<<inttree2<<std::endl;

        std::cout<<"---------  I  std::move Tree[1] into  Tree[2] : ---------"<<std::endl;
        inttree2=std::move(inttree1);

        std::cout<<"---------  Now Tree[1] is: ---------"<<std::endl;
        std::cout<<inttree1<<std::endl;

        std::cout<<"---------  While Tree[2] is: ---------"<<std::endl;
        std::cout<<inttree2<<std::endl;
    

         /* Test erase */
        std::cout<<"************Test Erase ************"<<std::endl;
        

        std::cout<<"I try to erase 7 "<<std::endl;
        inttree.erase(7);
        std::cout<<inttree<<std::endl;

        std::cout<<"I try to erase 2 "<<std::endl;
        inttree.erase(2);
        std::cout<<inttree<<std::endl;

        std::cout<<"I try to erase 3 "<<std::endl;
        inttree.erase(3);
        std::cout<<inttree<<std::endl;
        
        std::cout<<"I try to erase 3 (again!) "<<std::endl;
        inttree.erase(3);
        std::cout<<inttree<<std::endl;
        


         } catch (std::runtime_error& e) 
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
  
  return 0;
}