package com.example.t11;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.Base64;

@WebServlet(name = "encodeServlet", value = "/encode-servlet")
public class EncodeServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        PrintWriter out = resp.getWriter();
        String str = req.getParameter("field");
        String action = req.getParameter("action");
        out.println("<HTML><HEAD>");
        out.println("<TITLE>" + action + "</TITLE>");
        out.println("</HEAD><BODY><BR>");
        String result;
        if (action.equals("encode")) {
            out.println("<H1>Encoded string:<H1>");
            result = Base64.getEncoder().encodeToString(str.getBytes(StandardCharsets.UTF_8));
        } else {
            out.println("<H1>Decoded string:<H1>");
            result = new String(Base64.getDecoder().decode(str),StandardCharsets.UTF_8);
        }
        out.println("<input value = \"" + result + "\" size = \"100\">");
    }
}
