package logger;
import java.util.List;
import java.util.ArrayList;
public class Logger {

    LogEntryAbstractFactory log;
    List<LogEntry> liste;
    
    public Logger(LogEntryAbstractFactory log){
        this.log = log;
        this.liste = new ArrayList<>();
    }

    public void log(int value){
        this.liste.add(this.log.newIntEntry(value));
    }

    public void log(boolean value){
        this.liste.add(this.log.newBoolEntry(value));
    }

    public void printPrettyLog(){
        for(LogEntry element : this.liste){
            System.out.println(element.prettyPrint());
        }
    }

    public void printShortLog(){
        for(LogEntry element : this.liste){
            System.out.print(element.shortPrint());
        }
    }


}
