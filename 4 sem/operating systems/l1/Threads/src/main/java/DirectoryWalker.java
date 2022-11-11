import java.io.IOException;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.List;
import java.util.regex.PatternSyntaxException;

public class DirectoryWalker extends SimpleFileVisitor<Path> {

    private static final String DEFAULT_REGEX = ".*";
    private static final boolean DEFAULT_USE_SUB_DIRECTORIES = true;

    private final List<String> files;

    private final String regex;
    private boolean useSubDirs;
    private boolean fDirs;
    private boolean fFiles;
    private int maxDepth;

    protected DirectoryWalker(List<String> files, String regex) {
        this.files = files;
        this.regex = regex;
    }

    protected DirectoryWalker(List<String> files, String regex, boolean useSubDirs, boolean fFiles, boolean fDirs, int maxDepth) {
        this.files = files;
        this.regex = regex;
        this.useSubDirs = useSubDirs;
        this.fDirs = fDirs;
        this.fFiles = fFiles;
        this.maxDepth = maxDepth;
    }

    public static DirectoryWalker getInstance(List<String> paths, Path startDir) {
        return getInstance(
                paths,
                startDir,
                DEFAULT_REGEX,
                DEFAULT_USE_SUB_DIRECTORIES,
                true,
                true,
                Integer.MAX_VALUE
        );

    }

    public static DirectoryWalker getInstance(List<String> paths, Path startDir, String regex, boolean useSubDirs, boolean fDirs, boolean fFiles, int maxDepth) {
        DirectoryWalker directoryWalkerInstance = new DirectoryWalker(paths, regex, useSubDirs, fFiles, fDirs, maxDepth);
        try {
            Files.walkFileTree(startDir, directoryWalkerInstance);
        } catch (IOException e) {
            return null;
        }
        return directoryWalkerInstance;
    }

    private boolean first_time = true;

    int depth = 0;

    @Override
    public FileVisitResult preVisitDirectory(Path dir, BasicFileAttributes attrs) throws IOException {
        if ((!useSubDirs && !first_time) || depth > maxDepth)
            return FileVisitResult.SKIP_SUBTREE;
        try {
            if (fDirs && dir.getFileName().toString().matches(regex))
                files.add(dir.toString());
        } catch (PatternSyntaxException ignored) {}
        first_time = false;
        depth++;
        return FileVisitResult.CONTINUE;
    }

    @Override
    public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
        try {
            if (fFiles && file.getName(file.getNameCount() - 1).toString().matches(regex))
                files.add(file.toString());
        } catch (PatternSyntaxException ignored) {}
        return FileVisitResult.CONTINUE;
    }

    @Override
    public FileVisitResult postVisitDirectory(Path dir, IOException exc) throws IOException {
        if (!useSubDirs)
            return FileVisitResult.TERMINATE;
        depth--;
        return FileVisitResult.CONTINUE;
    }
}
