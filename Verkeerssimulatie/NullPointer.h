//
// Created by student on 25.02.19.
//
// Source: https://stackoverflow.com/questions/44517556/how-to-define-our-own-nullptr-in-c98
#ifndef VERKEERSSIMULATIE_NULLPOINTER_H
#define VERKEERSSIMULATIE_NULLPOINTER_H


const                         /* this is a const object...     */
class nullptr_t
{
public:
    template<class T>          /* convertible to any type       */
    operator T*() const        /* of null non-member            */
    { return 0; }           /* pointer...                    */

    template<class C, class T> /* or any type of null           */
    operator T C::*() const /* member pointer...             */
    { return 0; }

private:
    void operator&() const;    /* Can't take address of nullptr */

} nullptr = {};               /* and whose name is nullptr     */


#endif //VERKEERSSIMULATIE_NULLPOINTER_H
