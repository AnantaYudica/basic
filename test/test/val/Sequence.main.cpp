#include "test/val/Sequence.h"

#include <iostream>

int main()
{
    typedef basic::test::val::Sequence<int, 4> ValSeq4;
    ValSeq4 seq1(1, 2, 3, 4);
    std::cout << "seq1 at 0 : " << seq1.At<0>() << std::endl; 
    std::cout << "seq1 at 1 : " << seq1.At<1>() << std::endl;
    std::cout << "seq1 at 2 : " << seq1.At<2>() << std::endl;
    std::cout << "seq1 at 3 : " << seq1.At<3>() << std::endl;
    
    ValSeq4 seq2(seq1);
    
    std::cout << "seq2 at 0 : " << seq2.At<0>() << std::endl; 
    std::cout << "seq2 at 1 : " << seq2.At<1>() << std::endl;
    std::cout << "seq2 at 2 : " << seq2.At<2>() << std::endl;
    std::cout << "seq2 at 3 : " << seq2.At<3>() << std::endl;

    ValSeq4 seq3(std::move(seq1));
    std::cout << "seq3 at 0 : " << seq3.At<0>() << std::endl; 
    std::cout << "seq3 at 1 : " << seq3.At<1>() << std::endl;
    std::cout << "seq3 at 2 : " << seq3.At<2>() << std::endl;
    std::cout << "seq3 at 3 : " << seq3.At<3>() << std::endl;

    ValSeq4 seq4;
    seq4 = seq1;
    std::cout << "seq4 at 0 : " << seq4.At<0>() << std::endl; 
    std::cout << "seq4 at 1 : " << seq4.At<1>() << std::endl;
    std::cout << "seq4 at 2 : " << seq4.At<2>() << std::endl;
    std::cout << "seq4 at 3 : " << seq4.At<3>() << std::endl;
    
    ValSeq4 seq5;
    seq5 = std::move(seq1);
    std::cout << "seq5 at 0 : " << seq5.At<0>() << std::endl; 
    std::cout << "seq5 at 1 : " << seq5.At<1>() << std::endl;
    std::cout << "seq5 at 2 : " << seq5.At<2>() << std::endl;
    std::cout << "seq5 at 3 : " << seq5.At<3>() << std::endl;

    const ValSeq4 seq6 = seq1;
    std::cout << "seq6 at 0 : " << seq6.At<0>() << std::endl; 
    std::cout << "seq6 at 1 : " << seq6.At<1>() << std::endl;
    std::cout << "seq6 at 2 : " << seq6.At<2>() << std::endl;
    std::cout << "seq6 at 3 : " << seq6.At<3>() << std::endl;


}
