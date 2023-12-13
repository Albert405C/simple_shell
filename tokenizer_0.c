#include "shell.h"

/**
 * count_words - Count the number of words in a string.
 * @str: The input string.
 * @delim: The delimiter string.
 *
 * Return: The number of words.
 */
static int count_words(const char *str, const char *delim)
{
    int i, num_words = 0;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
            num_words++;
    }

    return num_words;
}

/**
 * extract_word - Extract a word from a string.
 * @str: The input string.
 * @delim: The delimiter string.
 * @index: A pointer to the current index in the string.
 *
 * Return: The extracted word.
 */
static char *extract_word(const char *str, const char *delim, int *index)
{
    int k, m;
    char *word;
    int i = *index;

    while (is_delim(str[i], delim))
        i++;

    k = 0;
    while (!is_delim(str[i + k], delim) && str[i + k])
        k++;

    word = malloc((k + 1) * sizeof(char));
    if (!word)
        return NULL;

    for (m = 0; m < k; m++)
        word[m] = str[i++];

    word[m] = '\0';

    return word;
}

/**
 * strtow - Splits a string into words. Repeat delimiters are ignored.
 * @str: The input string.
 * @delim: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *delim)
{
    int i, j, num_words = 0;
    char **result;

    if (str == NULL || str[0] == '\0')
        return NULL;

    if (!delim)
        delim = " ";

    num_words = count_words(str, delim);

    if (num_words == 0)
        return NULL;

    result = malloc((1 + num_words) * sizeof(char *));
    if (!result)
        return NULL;

    for (i = 0, j = 0; j < num_words; j++)
    {
        result[j] = extract_word(str, delim, &i);

        if (!result[j])
        {
            /* Handle memory allocation failure */
            for (int k = 0; k < j; k++)
                free(result[k]);
            free(result);
            return NULL;
        }
    }

    result[j] = NULL;
    return result;
}
