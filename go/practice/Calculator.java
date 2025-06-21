public class Calculator {
    public double eval(double a, double b, Operator op) {
        return op.eval(a, b);
    }
}

public enum Operator {
    ADD() {
        @Override
        double eval(final double a, final double b) {
            return a + b;
        }
    },
    SUB() {
        @Override
        double eval(final double a, final double b) {
            return a - b;
        }
    };
    abstract double eval(double a, double b);
}