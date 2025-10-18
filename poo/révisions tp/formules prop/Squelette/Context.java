import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.Iterator;

public class Context {
    public sealed static interface Formule permits Value, Variable, And, Or, Neg {
        public abstract String toString();
        public Formule substitute(Map<String, Formule> substitution);
    }

    /*à compléter*/

    private final static class Variable implements Formule {
        String name;
        public Variable(String v){
            this.name = v;
        }
        public String toString(){
            return this.name;
        }
        public Formule substitute(Map<String, Formule> substitution){
            if(substitution.containsKey(name)){
                return substitution.get(name);
            }
            return this;
        }
    }

    private final static class Value implements Formule{
        boolean value;

        public Value (boolean b){
            this.value = b;
        }
        public String toString(){
            return value ? "true" : "false";
        }

        public Formule substitute(Map<String, Formule> substitution){
            return this;
        }
    }

    private final static class And implements Formule{
        List<Formule> args;
        public And(List<Formule> args){
            this.args = List.copyOf(args);
        }
        public String toString(){
            StringBuilder sb = new StringBuilder();
            sb.append("and( ");
            for(int i = 0; i<args.size(); i++){
                sb.append(args.get(i).toString() + " ");
            }
            sb.append(")");
            return sb.toString();
        }
        public Formule substitute(Map<String, Formule> substitution){
            List<Formule> nvArgs = new ArrayList<Formule>();
            for(Formule elt : args){
                nvArgs.add(elt.substitute(substitution));
            }
            return new And(nvArgs);
        }
    }

    private final static class Or implements Formule{
        List<Formule> args;
        public Or(List<Formule> args){
            this.args = List.copyOf(args);
        }
        public String toString(){
            StringBuilder sb = new StringBuilder();
            sb.append("or( ");
            for(int i = 0; i<args.size(); i++){
                sb.append(args.get(i).toString() + " ");
            }
            sb.append(")");
            return sb.toString();
        }

        public Formule substitute(Map<String, Formule> substitution){
            List<Formule> nvArgs = new ArrayList<Formule>();
            for(Formule elt : args){
                nvArgs.add(elt.substitute(substitution));
            }
            return new Or(nvArgs);
        }
    }

    private final static class Neg implements Formule{
        Formule f;
        public Neg(Formule f){
            this.f = f;
        }
        public String toString(){
            return ("(not " + f.toString()+")");
        }
        public Formule substitute(Map<String, Formule> substitution){
            return new Neg(f.substitute(substitution));
        }
    }

    public static Formule Variable(String name) {
        return new Variable(name);
    }


    public static Formule Value(boolean value) {
        return new Value(value);
    }

    public static Formule And(List<Formule> arguments) {
        List<Formule> nvArgs = new ArrayList<Formule>();
        for(Formule elt : arguments){
            if(elt instanceof Value val){
                if(!val.value){
                    return new Value(false);
                }
                else{
                    continue;
                }
            }
            else{
                nvArgs.add(elt);
            }
            
        }
        if(nvArgs.isEmpty()){return new Value(true);}
        if(nvArgs.size() == 1){
            return nvArgs.get(0);
        }
        return new And(nvArgs);
    }

    public static Formule Or(List<Formule> arguments) {
        List<Formule> nvArgs = new ArrayList<Formule>();
        for(Formule elt : arguments){
            if(elt instanceof Value val){
                if(val.value){
                    return new Value(true);
                }
                else{
                    continue;
                }
            }
            else{
                nvArgs.add(elt);
            }
            
        }
        if(nvArgs.isEmpty()){return new Value(false);}
        if(nvArgs.size() == 1){
            return nvArgs.get(0);
        }
        return new Or(nvArgs);
    }

    public static Formule Neg(Formule argument) {
        if(argument instanceof Value val){
            return new Value(!val.value); //not true = false
        }
        if(argument instanceof Neg arg){
            return arg.f;
        }

        return new Neg(argument);
    }
}
