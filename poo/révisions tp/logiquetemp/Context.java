/*
My Name
*/

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Context {
    public sealed interface Formule permits Value, Variable, And, Neg, Or, Futur, Next, Until {
        /*à compléter*/

        // à définir quand vous arrivez à la section 2.3.
        public Formule substitute(Map<String, Formule> substitution);
    }

    private static record Value (boolean value) implements Formule {

        public Formule substitute(Map<String, Formule> substitution){
            return this;
        }

        @Override
        public String toString(){
            return value ? "true" : "false";
        }
    }

    private static record Variable(String variable) implements Formule{

        public Formule substitute(Map<String, Formule> substitution){
            if(substitution.containsKey(variable)){
                substitution.get(variable);
            }
            return this;
        }

        @Override
        public String toString(){
            return this.variable;
        }
    }

    private static record And(List<Formule> arguments) implements Formule{

        public And(List<Formule> arguments){
            this.arguments = List.copyOf(arguments);
        }

        public Formule substitute(Map<String, Formule> substitution){
            List<Formule> nvArgs = new ArrayList<Formule>();
            for(Formule elt : arguments){
                nvArgs.add(elt.substitute(substitution));
            }
            return new And(nvArgs);
        }

        @Override
        public String toString(){
            StringBuilder sb = new StringBuilder();
            sb.append("(and ");
            for(Formule elt : arguments){
                sb.append(elt.toString()+" ");
            }
            sb.append(")");
            return sb.toString();
        }
    }

    private static record Or(List<Formule> arguments) implements Formule{

        public Formule substitute(Map<String, Formule> substitution){
            List<Formule> nvArgs = new ArrayList<Formule>();
            for(Formule elt : arguments){
                nvArgs.add(elt.substitute(substitution));
            }
            return new Or(nvArgs);
        }

        @Override
        public String toString(){
            StringBuilder sb = new StringBuilder();
            sb.append("(or ");
            for(Formule elt : arguments){
                sb.append(elt.toString()+" ");
            }
            sb.append(")");
            return sb.toString();
        }
    }

    private static record Neg(Formule argument) implements Formule{

        public Formule substitute(Map<String, Formule> substitution){
            return new Neg(this.argument.substitute(substitution));
        }

        @Override
        public String toString(){
            StringBuilder sb = new StringBuilder();
            sb.append("(not " + argument.toString() + ")");
            return sb.toString();
        }
    }

    private static record Futur(Formule argument) implements Formule{

        public Formule substitute(Map<String, Formule> substitution){
            return new Futur(this.argument.substitute(substitution));
        }

        @Override
        public String toString(){
            StringBuilder sb = new StringBuilder();
            sb.append("(F " + argument.toString() + ")");
            return sb.toString();
        }
    }

    private static record Next(Formule argument) implements Formule{

        public Formule substitute(Map<String, Formule> substitution){
            return new Next(this.argument.substitute(substitution));
        }

        @Override
        public String toString(){
            StringBuilder sb = new StringBuilder();
            sb.append("(X " + argument.toString() + ")");
            return sb.toString();
        }
    }

    private static record Until(Formule argument1, Formule argument2) implements Formule{

        public Formule substitute(Map<String, Formule> substitution){
            return new Until(this.argument1.substitute(substitution), this.argument2.substitute(substitution));
        }

        @Override
        public String toString(){
            StringBuilder sb = new StringBuilder();
            sb.append("(U " + argument1.toString() + " " + argument2.toString() + ")");
            return sb.toString();
        }
    }

    public static Formule Variable(String name) {
        return new Variable(name);
    }


    public static Formule Value(boolean value) {
        return new Value(value);
    }

    public static Formule And(List<Formule> arguments) {
        return new And(arguments);
    }

    public static Formule Or(List<Formule> arguments) {
        return new Or(arguments);
    }

    public static Formule Neg(Formule argument) {
        return new Neg(argument);
    }

    public static Formule Next(Formule argument) {
        return new Next(argument);
    }

    public static Formule Futur(Formule argument) {
        return new Futur(argument);
    }

    public static Formule Until(Formule argument1, Formule argument2) {
        return new Until(argument1, argument2);
    }
}
