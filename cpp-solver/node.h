/* 
 * File:   node.h
 * Author: Lasse Lybeck
 *
 * Created on October 16, 2014, 12:38 PM
 */

#ifndef NODE_H
#define	NODE_H

namespace dlx {

    class node {
    public:
        node();
        node(const node&) = delete;
        virtual ~node();
        node*& left();
        node*& right();
        node*& up();
        node*& down();
        node*& column();
        int& value();
        int& index();
    private:
        node* left_;
        node* right_;
        node* up_;
        node* down_;
        node* column_;
        int value_;
        int index_;
    };

    node*& L(node*);
    node*& R(node*);
    node*& U(node*);
    node*& D(node*);
    node*& C(node*);
    int& V(node*);
    int& I(node*);

}

#endif	/* NODE_H */

