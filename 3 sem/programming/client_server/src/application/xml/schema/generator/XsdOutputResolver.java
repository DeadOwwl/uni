package application.xml.schema.generator;

import javax.xml.bind.SchemaOutputResolver;
import javax.xml.transform.Result;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.io.IOException;

class XsdOutputResolver extends SchemaOutputResolver {
	String baseDirName;
	String fileName;

	public XsdOutputResolver(String baseDirName, String fileName) {
		this.baseDirName = baseDirName;
		this.fileName = fileName.endsWith(".xsd") ? fileName : fileName + ".xsd";
	}

	@Override
	public Result createOutput(String namespaceUri, String suggestedFileName) throws IOException {
		File f = new File(baseDirName + File.separatorChar + fileName);
		if (!f.exists())
			f.createNewFile();
		return new StreamResult(f);
	}
}