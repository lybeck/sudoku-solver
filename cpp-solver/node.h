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
        node(node&);
        node(const node&) = delete;
        virtual ~node();
        node& left();
        node& right();
        node& up();
        node& down();
        node& column();
    private:
        node& left_;
        node& right_;
        node& up_;
        node& down_;
        node& column_;
    };

    node& L(node&);
    node& R(node&);
    node& U(node&);
    node& D(node&);
    node& C(node&);

}

#endif	/* NODE_H */

