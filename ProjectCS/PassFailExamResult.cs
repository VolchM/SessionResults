using System;

namespace SessionResultsCS
{
    // Результат зачёта
    public class PassFailExamResult : AttestationResult
    {
        // Получен ли зачёт
        public bool Passed { get; }


        public PassFailExamResult(bool passed)
        {
            Passed = passed;
        }


        public override string ToString()
        {
            return Passed ? "Зачёт" : "Незачёт";
        }

        public override string ToStringCompact()
        {
            return Passed ? "Зач" : "Нез";
        }

        public override int ToPercent()
        {
            return Passed ? MAX_PERCENT : 0;
        }

        public override bool IsPassed()
        {
            return Passed;
        }

        public override int ToScore()
        {
            return ToPercent();
        }
    }
}
