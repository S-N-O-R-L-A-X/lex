program -> compoundstmt
stmt -> ifstmt | whilestmt | assgstmt | compoundstmt
compoundstmt -> { stmts }
stmts -> stmt stmts | E
ifstmt -> if ( boolexpr ) then stmt else stmt
whilestmt -> while ( boolexpr ) stmt
assgstmt -> ID = arithexpr ;
boolexpr -> arithexpr boolop arithexpr
boolop -> < | > | <= | >= | ==
arithexpr -> multexpr arithexprprime
arithexprprime -> + multexpr arithexprprime | - multexpr arithexprprime | E
multexpr -> simpleexpr multexprprime
multexprprime -> * simpleexpr multexprprime | / simpleexpr multexprprime | E
simpleexpr -> ID | NUM | ( arithexpr )

I0:
program' -> .program
program -> .compoundstmt
compoundstmt -> .{ stmts }


I1:
program' -> program.

I2:
program -> compoundstmt.

I3:
compoundstmt -> { .stmts }
stmts -> .stmt stmts
stmts -> E
stmt -> .ifstmt 
stmt -> .whilestmt 
stmt -> .assgstmt 
stmt -> .compoundstmt
ifstmt -> .if ( boolexpr ) then stmt else stmt
whilestmt -> .while ( boolexpr ) stmt
assgstmt -> .ID = arithexpr ;
compoundstmt -> .{ stmts }

I4:
compoundstmt -> { stmts. }

(I3)I5:
stmts -> stmt .stmts
stmts -> .stmt stmts
stmts -> E
stmt -> .ifstmt 
stmt -> .whilestmt 
stmt -> .assgstmt 
stmt -> .compoundstmt
ifstmt -> .if ( boolexpr ) then stmt else stmt
whilestmt -> .while ( boolexpr ) stmt
assgstmt -> .ID = arithexpr ;
compoundstmt -> .{ stmts }

(I3)I6:
stmt -> ifstmt.