# include "myLeftistHeap_i127p615.hpp"
# include <iostream>
# include <vector>
# include <fstream>
# include <string>

void parseInstance(const std::string& line, std::vector<std::string> & res)
{
    int p = 0, q = 0;
    while(q < line.size())
    {
        if(line[q] ==',')
        {
            res.push_back(line.substr(p,q-p));
            p=q+1;
        }
        q++;
    }
}


int main(int argc, char* argv[])
{
  if(argc != 2)
  {
      std::cout << "You have to provide one test instance file to run the test main!\n";
      return 0;
  }

  std::ifstream fin;
  std::vector<std::string> data;
  fin.open(argv[1]);	    // open file
  if (!fin.is_open())	    // fail to open
  {
      std::cout << "Can't open the test instance file!\n";
      return 0;
  }
  else
  {
    std::string line;
    while(std::getline(fin, line))
    {
      parseInstance(line,data);
    }
  }

  // Declear three new leftist heap object
  myLeftistHeap<int>* mlh  = new myLeftistHeap<int>();
  myLeftistHeap<int>* mlh1 = new myLeftistHeap<int>();
  myLeftistHeap<int>* mlh_tem = new myLeftistHeap<int>();

  /*
    @Pre  New leftist heap has been decleared but no element has been put into it
    @Post Test your implementation of isEmpty function to tell if the heap is empty
  */
  if(mlh->isEmpty())	std::cout << 1 << "\n";
  else                std::cout << 0 << "\n";

  for(int i = 0; i < data.size(); ++i)
  {
    int it = std::stoi(data[i]);
    /*
      @Pre  Load a new element
      @Post Insert the new element to mlh. Insert the new element to mlh_tem if
            the index of the element is odd. Note that a single element will be
            treated as a single-node leftist heap.
    */
    mlh->insert(it);
    if(i%2==1) mlh_tem->insert(it);
  }


  mlh->printInOrder();      // Test your implementation of in-order traversal
  *mlh1 = *mlh;             // Test your implementation of assign operator
  // Test your implementation of copy constructor
  myLeftistHeap<int>* mlh2 = new myLeftistHeap<int>(*mlh);
  /*
    @Pre  mlh1 and mlh2 should be exactly the same as mlh
    @Post Print the in-order of mlh1, print the level-order traversal of mlh2.
          you should be able to reconstruct the tree-structure of mlh now.
  */
  mlh1->printInOrder();
  mlh2->printLevelOrder();


  if(mlh1->isEmpty())	std::cout << 1 << "\n";
  else                std::cout << 0 << "\n";
  mlh1->makeEmpty();        // Test your implementation of makeEmpty
  if(mlh1->isEmpty())	std::cout << 1 << "\n";
  else                std::cout << 0 << "\n";
  /*
    Test your implementation of deleteMin, boundary case when you try to deleteMin
    from empty heap.
  */
  mlh1->deleteMin();


  std::cout << mlh->findMin() << "\n";    // Test your implementation of findMin
  for(int i = 0; i < 5; i++)
  {
    int a;
    /*
      Test your implementation of deleteMin, where you return the to-be-delete
      element by reference. This is a combination of findMin and deleteMin.
    */
    mlh->deleteMin(a);
    std::cout << a << "\n";
  }
  // Now check if your leftist heap is correct
  mlh->printLevelOrder();
  mlh->printInOrder();

  for(int i = 0; i < 5; i++)
  {
    // Test your implementation of deleteMin, this time you discard the min element.
    mlh->deleteMin();
  }
  // Now check if your leftist heap is correct
  mlh->printLevelOrder();
  mlh->printInOrder();

  // Test the merge routine of your leftist heap by merging mlh_tem with mlh
  mlh_tem->printInOrder();
  mlh->merge(*mlh_tem);
  mlh->printLevelOrder();

  delete mlh;
  delete mlh_tem;
  delete mlh1;
  delete mlh2;
  return 0;
}
