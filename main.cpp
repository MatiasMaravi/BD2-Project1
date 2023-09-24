#include "extendible_hashing.h"
int main(){
    
    DynamicHash dh("buckets.dat","indices.dat");
/*
    Record r1(1,"leo",3);
    Record r2(2,"juan",3);
    Record r3(3,"pedro",3);
    Record r4(4,"maria",3);
    Record r5(5,"jose",3);
    Record r6(6,"luis",3);
    Record r7(10,"luis",3);
    Record r8(15,"luis",3);
    Record r9(20,"luis",3);
    Record r10(25,"luis",3);
    Record r11(23,"luis",3);
    Record r12(24,"luis",3);
    Record r13(12,"luis",3);
    Record r14(13,"luis",3);
    Record r15(53,"luis",3);
    Record r16(54,"luis",3);
    Record r17(42,"luis",3);
    Record r18(102,"luis",3);
    Record r19(103,"luis",3);
    Record r20(1130,"luis",3);
    Record r21(2021,"luis",3);
    Record r22(2022,"luis",3);
    Record r23(2023,"luis",3);
    Record r24(3054,"luis",3);

    
    dh.add(r1);
    dh.add(r2);
    dh.add(r3);
    dh.add(r4);
    dh.add(r5);
    dh.add(r6);
    dh.add(r7);
    dh.add(r8);
    dh.add(r9);
    dh.add(r10);
    dh.add(r11);
    dh.add(r12);
    dh.add(r13);
    dh.add(r14);
    dh.add(r15);
    dh.add(r16);
    dh.add(r17);
    dh.add(r18);
    dh.add(r19);
    dh.add(r20);
    dh.add(r21);
    dh.add(r22);
    dh.add(r23);
    dh.add(r24);

*/

    Record r100= dh.search(25);
    r100.print();
   
    
    return 0;
}