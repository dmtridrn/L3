package logger;

public interface LogEntryAbstractFactory {
    
    public LogEntry newIntEntry(int value);
    public LogEntry newBoolEntry(boolean value);
}
