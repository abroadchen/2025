<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8"/>
  <title>Upload File</title>
</head>
<body>
  <form action="/upload?hello=world&thread=123" method="post" enctype="multipart/form-data">
    <input type="text" name="hello" value="world" />
    <input type="text" name="post" value="456" />
    <input type="file" name="uploaded">
    <input type="submit" value="提交">
   </form>
</body>
</html>