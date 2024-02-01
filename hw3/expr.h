#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <stdexcept>

// Abstract base class for all expressions
class Expr {
public:
    virtual ~Expr() {}

    // Evaluate the expression and return the result
    virtual int interp() const = 0;

    // Check if the expression contains any variables
    virtual bool has_variable() const = 0;

    // Perform substitution of a variable with another expression
    virtual Expr* subst(const std::string& varName, const Expr* replacement) const = 0;

    // Check if this expression equals another expression
    virtual bool equals(const Expr* other) const = 0;
};

// Represents a numeric constant in an expression
class Num : public Expr {
    int value;
public:
    Num(int value) : value(value) {}
    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& varName, const Expr* replacement) const override;
    bool equals(const Expr* other) const override;
};

// Represents an addition operation in an expression
class Add : public Expr {
    Expr* lhs;
    Expr* rhs;
public:
    Add(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
    ~Add();

    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& varName, const Expr* replacement) const override;
    bool equals(const Expr* other) const override;
};

// Represents a multiplication operation in an expression
class Mult : public Expr {
    Expr* lhs;
    Expr* rhs;
public:
    Mult(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {}
    ~Mult();

    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& varName, const Expr* replacement) const override;
    bool equals(const Expr* other) const override;
};

// Represents a variable in an expression
class VarExpr : public Expr {
    std::string name;
public:
    VarExpr(const std::string& name) : name(name) {}

    int interp() const override;
    bool has_variable() const override;
    Expr* subst(const std::string& varName, const Expr* replacement) const override;
    bool equals(const Expr* other) const override;
};

#endif // EXPR_H
