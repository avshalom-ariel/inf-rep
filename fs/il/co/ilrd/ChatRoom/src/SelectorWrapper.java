import java.io.*;
import java.nio.channels.*;
import java.util.*;

public class SelectorWrapper {
    private final Selector selector;

    public SelectorWrapper() throws IOException {
        selector = Selector.open();
    }

    public int select() throws IOException {
        return selector.select();
    }

    public Set<SelectionKey> selectedKeys() {
        return selector.selectedKeys();
    }

    public void wakeup() {
        selector.wakeup();
    }

    public void close() throws IOException {
        selector.close();
    }

    public void registerTCPServer(ServerSocketChannel server, int selectionKey) throws ClosedChannelException {
        server.register(selector, selectionKey);
    }

    public void registerTCP(SocketChannel server, int selectionKey) throws ClosedChannelException {
        server.register(selector, selectionKey);
    }
}
