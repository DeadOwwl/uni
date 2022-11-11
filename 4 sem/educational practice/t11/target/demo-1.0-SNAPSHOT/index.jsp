<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>JSP - Hello World</title>
</head>
<body>
<h1><%= "Base64" %>
</h1>
<br/>
<form action="encode-servlet">
    <input type="text" name="field" size="100"/>
    <p><input type="radio" name="action" value="encode">Encode</p>
    <p><input type="radio" name="action" value="decode"/>Decode<p>
    <button type="submit">Submit</button>
</form>
</body>
</html>