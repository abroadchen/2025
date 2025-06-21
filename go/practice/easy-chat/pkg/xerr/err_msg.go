package xerr

var codeText = map[int]string{
	SERVER_COMMON_ERROR: "server error",
	REQUEST_PARAM_ERROR: "request parameter error",
	DB_ERROR:            "db error",
}

func ErrMsg(errcode int) string {
	if msg, ok := codeText[errcode]; ok {
		return msg
	}
	return codeText[errcode]
}
