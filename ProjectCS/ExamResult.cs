using System;

namespace SessionResults
{
    // Результат экзамена
    public class ExamResult : AttestationResult
    {
        public const int MIN_SCORE = 0;
        public const int MAX_SCORE = 100;
        public const int PASS_SCORE = 25;


        // Полученный балл за экзамен
        public int Score { get; }


        public ExamResult(int score) {
            Score = score;
        }


        public override string ToString()
        {
            return Score.ToString();
        }

        public override string ToStringCompact()
        {
            return Score.ToString();
        }

        public override int ToPercent()
        {
            return ((Score - MIN_SCORE) * MAX_PERCENT / (MAX_SCORE - MIN_SCORE));
        }

        public override bool IsPassed()
        {
            return Score >= PASS_SCORE;
        }

        public override int ToScore()
        {
            return Score;
        }
    }
}
