#include "catch.h"
#include "expr.h"
#include "cmdline.h"
//Added Tests  ss
TEST_CASE("NumExpr operations") {
    Num num(5);

    SECTION("Interpretation") {
        CHECK(num.interp() == 5);
    }

    SECTION("Variable presence") {
        CHECK_FALSE(num.has_variable());
    }

    SECTION("Substitution") {
        Num* substituted = dynamic_cast<Num*>(num.subst("x", new Num(10)));
        REQUIRE(substituted != nullptr);
        CHECK(substituted->interp() == 5);
        delete substituted;
    }

    SECTION("Equality") {
        Num numEqual(5);
        Num numNotEqual(3);
        CHECK(num.equals(&numEqual));
        CHECK_FALSE(num.equals(&numNotEqual));
    }
}

TEST_CASE("VarExpr operations") {
    VarExpr var("x");

    SECTION("Interpretation") {
        CHECK_THROWS_WITH(var.interp(), "No value for variable");
    }

    SECTION("Variable presence") {
        CHECK(var.has_variable());
    }

    SECTION("Substitution") {
        Expr* substituted = var.subst("x", new Num(5));
        CHECK(substituted->interp() == 5);
        delete substituted;

        Expr* notSubstituted = var.subst("y", new Num(5));
        CHECK(notSubstituted->equals(&var));
        delete notSubstituted;
    }
}

TEST_CASE("AddExpr operations") {
    Add add(new Num(3), new Num(4));
    Add addWithVar(new VarExpr("x"), new Num(7));
    SECTION("Equal"){
        CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(2),new Num(3)))==true );
        CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(3),new Num(2)))==false );
        CHECK( (new Add(new Num(-2),new Num(-3)))->equals(new Add(new Num(-2),new Num(-3)))==true );
        CHECK( (new Add(new Num(-2),new Num(0)))->equals(new Add(new Num(-2),new Num(0)))==true );
    }
    SECTION("Interpretation") {
        CHECK(add.interp() == 7);
        CHECK_THROWS_WITH(addWithVar.interp(), "No value for variable");
    }

    SECTION("Variable presence") {
        CHECK_FALSE(add.has_variable());
        CHECK(addWithVar.has_variable());
    }

    SECTION("Substitution") {
        Expr* substituted = addWithVar.subst("x", new Num(5));
        CHECK(substituted->interp() == 12);
        delete substituted;
    }
}

TEST_CASE("MultExpr operations") {
    Mult mult(new Num(4), new Num(2));
    Mult multWithVar(new VarExpr("x"), new Num(7));
    SECTION("Equal"){
        CHECK( (new Mult(new Num(2),new Num(3)))->equals(new Mult(new Num(3),new Num(2)))==false );
        CHECK( (new Mult(new Num(2),new Num(3)))->equals(new Mult(new Num(2),new Num(3)))==true );
        CHECK( (new Mult(new Num(-2),new Num(-3)))->equals(new Mult(new Num(-2),new Num(-3)))==true );
        CHECK( (new Mult(new Num(-2),new Num(0)))->equals(new Mult(new Num(-2),new Num(0)))==true );
    }
    SECTION("Interpretation") {
        CHECK(mult.interp() == 8);
        CHECK_THROWS_WITH(multWithVar.interp(), "No value for variable");
    }

    SECTION("Variable presence") {
        CHECK_FALSE(mult.has_variable());
        CHECK(multWithVar.has_variable());
    }

    SECTION("Substitution") {
        Expr* substituted = multWithVar.subst("x", new Num(5));
        CHECK(substituted->interp() == 35);
        delete substituted;
    }
}

TEST_CASE("Complex Expression Evaluation") {
    Add complexExpr(new Add(new Num(2), new Mult(new Num(3), new VarExpr("x"))), new Num(4));
    CHECK_THROWS_WITH(complexExpr.interp(), "No value for variable");
    Expr* substitutedExpr = complexExpr.subst("x", new Num(2));
    CHECK(substitutedExpr->interp() == 12);
    delete substitutedExpr;
}

TEST_CASE("Special Cases") {
    Add zeroTest(new Num(0), new Num(0));
    CHECK(zeroTest.interp() == 0);

    Mult negativeTest(new Num(-1), new Num(5));
    CHECK(negativeTest.interp() == -5);
}
void test_no_arguments() {
    const char* argv[] = {"program_name"};
    try {
        use_arguments(1, const_cast<char**>(argv));
        // Check that no exception is thrown when no arguments are provided.
    } catch (const std::runtime_error& e) {
        // Handle the error: this is unexpected.
    }
}

void test_help_argument() {
    const char* argv[] = {"program_name", "--help"};
    try {
        use_arguments(2, const_cast<char**>(argv));
    } catch (const std::runtime_error& e) {
        // Check that the exception message is "help shown".
    }
}

void test_test_argument() {
    const char* argv[] = {"program_name", "--test"};
    try {
        use_arguments(2, const_cast<char**>(argv));
        // Check that no exception is thrown when "--test" is provided.
    } catch (const std::runtime_error& e) {
        // Handle the error: this is unexpected.
    }
}