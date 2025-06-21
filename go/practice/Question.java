public class Question {

    private final Map<String, Function<String, String>> answers = new HashMap<>();

    public Question() {
        answers.put("What is your name?", (name) -> "My name is " + name);
    }

    public String handle(String type, String detail) {
        return Optional.ofNullable(answers.get(type)).map(function -> function.apply(detail));
    }
}