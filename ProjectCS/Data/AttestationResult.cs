using System;

namespace SessionResultsCS
{
    // Абстрактный класс - Результат аттестации
    public abstract class AttestationResult
    {
        public const int MAX_PERCENT = 100;


        // Преобразует результат в строку
        public abstract override string ToString();

        // Преобразует результат в короткую строку
        public abstract string ToStringCompact();

        // Преобразует результат в процент выполнения
        public abstract int ToPercent();

        // Возвращает, сдана ли аттестация
        public abstract bool IsPassed();

        // Возвращает балл для расчёта среднего балла
        public abstract int ToScore();
    }
}
