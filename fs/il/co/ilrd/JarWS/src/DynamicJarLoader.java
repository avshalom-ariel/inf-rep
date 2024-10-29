import java.io.IOException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.jar.*;

public class DynamicJarLoader {
    private ArrayList<Class<?>> classes = new ArrayList<>();
    private final String interfaceName;
    private final String jarFilePath;

    private DynamicJarLoader(String interfaceName, String jarFilePath) {
        this.interfaceName = interfaceName;
        this.jarFilePath = jarFilePath;
    }

    public void load() {
        try {
            JarFile jarFile = new JarFile(jarFilePath);
            Enumeration<JarEntry> enumeration = jarFile.entries();
            URL[] urls = { new URL("jar:file:" + jarFilePath + "!/") };
            URLClassLoader classLoader = URLClassLoader.newInstance(urls);
            while (enumeration.hasMoreElements()) {
                JarEntry jarEntry = enumeration.nextElement();
                if (jarEntry.isDirectory() || !jarEntry.getName().endsWith(".class")) {
                    continue;
                }
                System.out.println("Loading " + jarEntry.getName());
                String className = jarEntry.getName().substring(0,jarEntry.getName().length()-6);
//                className = className.replace('/', '.'); ??learn more
                Class<?> c = classLoader.loadClass(className);
                Class<?>[] interfaces = c.getInterfaces();
                for (Class<?> i : interfaces) {
                    if (i.getName().equals(interfaceName)) {
                        classes.add(c);
                    }
                }
            }
            for (Class<?> i : classes) {
                System.out.println(i.getName());
            }

        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        DynamicJarLoader dynamicJarLoader = new DynamicJarLoader("DummyInterface", "/home/avshalom/git/fs/il/co/ilrd/JarWS/src/myJar.jar");
        dynamicJarLoader.load();
    }
}
