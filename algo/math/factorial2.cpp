#pragma GCC optimize(2)
#include <bits/stdc++.h>
using LL = long long;
class ModLL
{
    static inline LL M = 998244353;
    LL n;
    static LL inv(LL x)
    {
        return x == 1 ? x : __int128(M - M / x) * inv(M % x) % M;
    }

public:
    template <typename T>
    operator T() const
    {
        return static_cast<T>(n);
    }
    static void setMod(LL m)
    {
        M = m;
    }
    static LL mod()
    {
        return M;
    }
    static ModLL raw(LL x)
    {
        ModLL A;
        A.n = x;
        return A;
    }
    ModLL()
    {
        n = 0;
    }
    ModLL(const int &x) : n(x % M)
    {
        if (n < 0)
            n += M;
    }
    ModLL(const LL &x) : n(x % M)
    {
        if (n < 0)
            n += M;
    }
    ModLL(const __int128 &x) : n(x % M)
    {
        if (n < 0)
            n += M;
    }
    ModLL operator-() const
    {
        return n == 0 ? *this : raw(M - n);
    }
    ModLL &operator++()
    {
        if (++n == M)
            n = 0;

        return *this;
    }
    ModLL &operator--()
    {
        if (--n == -1)
            n += M;

        return *this;
    }
    ModLL &operator+=(const ModLL &A)
    {
        n += A.n;

        if (n >= M)
            n -= M;
        return (*this);
    }
    ModLL &operator-=(const ModLL &A)
    {
        n -= A.n;

        if (n < 0)
            n += M;
        return (*this);
    }
    ModLL &operator*=(const ModLL &A)
    {
        n = __int128(n) * A.n % M;
        return (*this);
    }
    ModLL &operator/=(const ModLL &A)
    {
        return (*this) *= A.inv();
    }
    ModLL operator+(const ModLL &A) const
    {
        return ModLL(*this) += A;
    }
    ModLL operator-(const ModLL &A) const
    {
        return ModLL(*this) -= A;
    }
    ModLL operator*(const ModLL &A) const
    {
        return ModLL(*this) *= A;
    }
    ModLL operator/(const ModLL &A) const
    {
        return ModLL(*this) /= A;
    }
    ModLL operator<<(int x) const
    {
        static constexpr int bits = 64;
        __int128 r = n;
        while (x > bits)
        {
            x -= bits;
            r <<= bits;
            r %= M;
        }
        r <<= x;
        return ModLL(r);
    }
    ModLL &operator<<=(int x)
    {
        return (*this) = (*this) << x;
    }
    bool operator==(const ModLL &A) const
    {
        return n == A.n;
    }
    bool operator!=(const ModLL &A) const
    {
        return n != A.n;
    }
    ModLL inv() const
    {
        return inv(n);
    }
    friend ModLL pow(ModLL A, LL n)
    {
        ModLL R(1);

        while (n)
        {
            if (n & 1)
                R *= A;
            n >>= 1;
            A *= A;
        }
        return R;
    }
    friend std::istream &operator>>(std::istream &in, ModLL &A)
    {
        LL x;
        in >> x;
        A = ModLL(x);
        return in;
    }
    friend std::ostream &operator<<(std::ostream &out, const ModLL &A)
    {
        out << A.n;
        return out;
    }
};
template <int N>
class MInt
{
    static inline constexpr int M = N;
    int n;
    static int inv(int x)
    {
        return x == 1 ? x : 1LL * (M - M / x) * inv(M % x) % M;
    }

public:
    template <typename T>
    operator T() const
    {
        return static_cast<T>(n);
    }
    static void setMod(int m)
    {
        M = m;
    }
    static MInt raw(int x)
    {
        MInt A;
        A.n = x;
        return A;
    }
    MInt()
    {
        n = 0;
    }
    MInt(const int &x) : n(x % M)
    {
        if (n < 0)
            n += M;
    }
    MInt(const LL &x) : n(x % M)
    {
        if (n < 0)
            n += M;
    }
    MInt operator-() const
    {
        return n == 0 ? *this : raw(M - n);
    }
    MInt &operator++()
    {
        if (++n == M)
            n = 0;

        return *this;
    }
    MInt &operator--()
    {
        if (--n == -1)
            n += M;

        return *this;
    }
    MInt &operator+=(const MInt &A)
    {
        n += A.n;

        if (n >= M)
            n -= M;

        return (*this);
    }
    MInt &operator-=(const MInt &A)
    {
        n -= A.n;

        if (n < 0)
            n += M;

        return (*this);
    }
    MInt &operator*=(const MInt &A)
    {
        n = 1LL * n * A.n % M;
        return (*this);
    }
    MInt operator+(const MInt &A) const
    {
        return MInt(*this) += A;
    }
    MInt operator-(const MInt &A) const
    {
        return MInt(*this) -= A;
    }
    MInt operator*(const MInt &A) const
    {
        return MInt(*this) *= A;
    }
    MInt operator<<(int x) const
    {
        static constexpr int bits = 32;
        LL r = n;

        while (x > 32)
        {
            x -= 32;
            r <<= 32;
            r %= M;
        }
        r <<= x;
        return MInt(r);
    }
    MInt &operator<<=(int x)
    {
        return (*this) = (*this) << x;
    }
    bool operator==(const MInt &A) const
    {
        return n == A.n;
    }
    bool operator!=(const MInt &A) const
    {
        return n != A.n;
    }
    MInt inv() const
    {
        return inv(n);
    }
    friend MInt pow(MInt A, int n)
    {
        MInt R(1);

        while (n)
        {
            if (n & 1)
                R *= A;

            n >>= 1;
            A *= A;
        }
        return R;
    }
    friend std::istream &operator>>(std::istream &in, MInt &A)
    {
        LL x;
        in >> x;
        A = MInt(x);
        return in;
    }
    friend std::ostream &operator<<(std::ostream &out, const MInt &A)
    {
        out << A.n;
        return out;
    }
};
template <int M>
class NTT
{
    std::vector<int> rev;
    std::vector<MInt<M>> roots{0, 1};

public:
    static inline const MInt<M> g = 3;
    void dft(std::vector<MInt<M>> &a)
    {
        int n = a.size();

        if ((int)rev.size() != n)
        {
            int k = __builtin_ctz(n) - 1;
            rev.resize(n);
            for (int i = 0; i < n; ++i)
            {
                rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
            }
        }

        if ((int)roots.size() < n)
        {
            int k = __builtin_ctz(roots.size());
            roots.resize(n);

            while ((1 << k) < n)
            {
                auto e = pow(g, (M - 1) >> (k + 1));

                for (int i = 1 << (k - 1); i < (1 << k); ++i)
                {
                    roots[2 * i] = roots[i];
                    roots[2 * i + 1] = roots[i] * e;
                }

                ++k;
            }
        }
        for (int i = 0; i < n; ++i)
            if (rev[i] < i)
            {
                std::swap(a[i], a[rev[i]]);
            }
        for (int k = 1; k < n; k *= 2)
        {
            for (int i = 0; i < n; i += 2 * k)
            {
                for (int j = 0; j < k; ++j)
                {
                    auto u = a[i + j], v = a[i + j + k] * roots[k + j];
                    a[i + j] = u + v;
                    a[i + j + k] = u - v;
                }
            }
        }
    }
    void idft(std::vector<MInt<M>> &a)
    {
        int n = a.size();
        std::reverse(a.begin() + 1, a.end());
        dft(a);
        auto inv = pow(MInt<M>(n), M - 2);

        for (auto &x : a)
            x *= inv;
    }
};
template <typename valT>
class BinomModp
{
    BinomModp()
    {
        fac.reserve(1000002), ifac.reserve(1000002), inv.reserve(1000002);
    }
    void init(int n)
    {
        assert(n <= valT::mod());
        fac[0] = 1;

        for (int i(1); i < n; ++i)
            fac[i] = fac[i - 1] * valT::raw(i);

        ifac[n - 1] = fac[n - 1].inv();

        for (int i(n - 1); i; --i)
            ifac[i - 1] = ifac[i] * valT::raw(i);

        for (int i(1); i < n; ++i)
            inv[i] = ifac[i] * fac[i - 1];
    }

public:
    std::vector<valT> fac, ifac, inv;
    BinomModp(const BinomModp &) = delete;
    static BinomModp &Instance(int N = 0)
    {
        static BinomModp instance;

        if (N)
            instance.init(N);

        return instance;
    }
};
using LL = long long;
template <typename T, typename valT>
class Poly : public T
{
    static inline const valT j = pow(valT(3), (valT::mod() - 1) >> 2);
    static inline const valT inv2 = (valT::mod() + 1) >> 1;
    static inline const auto &Binom = BinomModp<valT>::Instance(1000002);

public:
    using T::T;
    static void setMod(LL p, int n = 1000002)
    {
        valT::setMod(p);
        BinomModp<valT>::Instance(std::min(LL(n), p));
    }
    Poly(const T &x) : T(x) {}
    Poly mulXn(int n) const
    {
        std::vector<valT> b = *this;
        b.insert(b.begin(), n, 0);
        return Poly(b);
    }
    Poly modXn(int n) const
    {
        if (n > (int)this->size())
            return *this;

        return Poly({this->begin(), this->begin() + n});
    }
    Poly divXn(int n) const
    {
        if ((int)this->size() <= n)
            return Poly();

        return Poly({this->begin() + n, this->end()});
    }
    Poly operator-() const
    {
        auto A = *this;

        for (auto &x : A)
            x = -x;

        return A;
    }
    Poly &operator+=(const Poly &rhs)
    {
        if (this->size() < rhs.size())
            this->resize(rhs.size());

        for (int i = 0, nr = rhs.size(); i < nr; ++i)
            (*this)[i] += rhs[i];

        this->standard();
        return *this;
    }
    Poly &operator-=(const Poly &rhs)
    {
        if (this->size() < rhs.size())
            this->resize(rhs.size());

        for (int i = 0, nr = rhs.size(); i < nr; ++i)
            (*this)[i] -= rhs[i];

        this->standard();
        return *this;
    }
    Poly operator+(const Poly &rhs) const
    {
        return Poly(*this) += rhs;
    }
    Poly operator-(const Poly &rhs) const
    {
        return poly(*this) -= rhs;
    }
    Poly operator*(const Poly &rhs) const
    {
        return this->mul(rhs);
    }
    Poly inv(int n) const
    {
        Poly x((*this)[0].inv());
        int k = 1;

        while (k < n)
        {
            k *= 2;
            x *= (Poly(2) - this->modXn(k) * x).modXn(k);
        }
        return x.modXn(n);
    }
    Poly &operator/=(Poly rhs)
    {
        int n = this->size(), m = rhs.size();

        if (n < m)
            return (*this) = Poly();

        this->reverse();
        rhs.reverse();
        (*this) *= rhs.inv(n - m + 1);
        this->resize(n - m + 1);
        this->reverse();
        return *this;
    }
    Poly &operator%=(const Poly &rhs)
    {
        return *this -= (*this) / rhs * rhs;
    }
    Poly operator%(const Poly &rhs) const
    {
        return Poly(*this) %= rhs;
    }
    Poly derivation() const
    {
        if (this->empty())
            return Poly();

        int n = this->size();
        std::vector<valT> r(n - 1);

        for (int i = 1; i < n; ++i)
            r[i - 1] = (*this)[i] * valT(i);

        return Poly(r);
    }
    Poly mulT(Poly rhs) const
    {
        if (rhs.size() == 0)
            return Poly();

        int n = rhs.size();
        std::reverse(rhs.begin(), rhs.end());
        return ((*this) * rhs).divXn(n - 1);
    }
    std::vector<valT> evals(std::vector<valT> x) const
    {
        if (this->size() == 0)
            return std::vector<valT>(x.size());

        int n = x.size();
        std::vector<valT> ans(n);
        std::vector<Poly> g(4 * n);
        std::function<void(int, int, int)> build = [&](int l, int r, int p)
        {
            if (r - l == 1)
            {
                g[p] = Poly({1, -x[l]});
            }
            else
            {
                int m = (l + r) / 2;
                build(l, m, 2 * p);
                build(m, r, 2 * p + 1);
                g[p] = g[2 * p] * g[2 * p + 1];
            }
        };
        build(0, n, 1);
        std::function<void(int, int, int, const Poly &)> solve = [&](int l, int r, int p, const Poly &f)
        {
            if (r - l == 1)
            {
                ans[l] = f.at(0);
            }
            else
            {
                int m = (l + r) / 2;
                solve(l, m, 2 * p, f.mulT(g[2 * p + 1]).modXn(m - l));
                solve(m, r, 2 * p + 1, f.mulT(g[2 * p]).modXn(r - m));
            }
        };
        solve(0, n, 1, mulT(g[1].inv(this->size())).modXn(n));
        return ans;
    }
    // Biết h(0), h(1), ..., h(d)
    // Hàm trả về h(m), h(m + 1), ..., h(m + cnt - 1)
    // m > d
    static std::vector<valT> valToVal(std::vector<valT> h, valT m, int cnt)
    {
        int d = h.size() - 1;
        // tính h[i] = (-1)^(d-i) h(i)/(i! (d-i)!)
        // hệ số x^i
        for (int i = 0; i <= d; ++i)
        {
            h[i] *= Binom.ifac[i] * Binom.ifac[d - i];
            if ((d - i) & 1)
                h[i] = -h[i];
        }

        // tính f[i] = 1/(m+i-d)
        //  hệ số x^(m + cnt - 1 - i)
        std::vector<valT> f(d + cnt);
        auto now = m - valT(d);

        for (int i = 0; i < d + cnt; ++i)
        {
            f[i] = now.inv();
            ++now;
        }

        // Nhân 2 đa thức
        h = Poly(f) * Poly(h);
        h.resize(d + cnt);
        // chỉ lấy hệ số x^(m) đến x^(m+cnt-1)
        h = std::vector<valT>(h.begin() + d, h.end());
        now = 1;

        for (int i(0); i <= d; ++i)
            now *= m - valT::raw(i);

        h[0] *= now;

        for (int i = 1; i < cnt; ++i)
        {
            now *= m + valT::raw(i);
            now *= (m + valT(i - d - 1)).inv();
            h[i] *= now;
        }

        return h;
    };
};
template <typename valT>
class PolyBase : public std::vector<valT>
{
protected:
    void standard()
    {
        while (!this->empty() && this->back() == valT(0))
            this->pop_back();
    }
    void reverse()
    {
        std::reverse(this->begin(), this->end());
        this->standard();
    }

public:
    PolyBase() {}
    PolyBase(const std::vector<valT> &a) : std::vector<valT>{a}
    {
        standard();
    }
    PolyBase(const valT &x) : std::vector<valT>{x}
    {
        standard();
    }
    valT at(int id) const
    {
        if (id < 0 || id >= (int)this->size())
            return 0;

        return (*this)[id];
    }
};
class PolyBaseMFT4 : public PolyBase<ModLL>
{
public:
    static const int M0 = 595591169, M1 = 645922817, M2 = 897581057, M3 = 998244353;
    static const LL M01 = 384705925660803073LL, M23 = 896005221510021121LL;
    static const __int128 M0123 = __int128(384705925660803073LL) * 896005221510021121LL;
    static const int t01 = 538269027, t23 = 415935157;
    static inline NTT<595591169> ntt0;
    static inline NTT<645922817> ntt1;
    static inline NTT<897581057> ntt2;
    static inline NTT<998244353> ntt3;
    using PolyBase<ModLL>::PolyBase;

protected:
    static ModLL crt(int a0, int a1, int a2, int a3)
    {
        LL ans1 = a0 + LL(a1 - a0) * t01 % M1 * M0;
        LL ans2 = a2 + LL(a3 - a2) * t23 % M3 * M2;
        __int128 ans = ans1 + __int128(ans2 - ans1) * 341204425684314487LL % M23 * M01;

        if (ans < 0)
            ans += M0123;

        return ModLL(ans);
    }
    PolyBaseMFT4 mul(const PolyBaseMFT4 &rhs) const
    {
        int tot = std::max(1, int(this->size() + rhs.size() - 1));
        int sz = 1 << std::__lg(tot * 2 - 1);
        std::vector<MInt<M0>> a0(sz), b0(sz);
        std::vector<MInt<M1>> a1(sz), b1(sz);
        std::vector<MInt<M2>> a2(sz), b2(sz);
        std::vector<MInt<M3>> a3(sz), b3(sz);

        for (int i = 0, ns = this->size(); i < ns; ++i)
        {
            LL tmp = (*this)[i];
            a0[i] = tmp;
            a1[i] = tmp;
            a2[i] = tmp;
            a3[i] = tmp;
        }

        for (int i = 0, ns = rhs.size(); i < ns; ++i)
        {
            LL tmp = rhs[i];
            b0[i] = tmp;
            b1[i] = tmp;
            b2[i] = tmp;
            b3[i] = tmp;
        }

        ntt0.dft(a0);
        ntt0.dft(b0);
        ntt1.dft(a1);
        ntt1.dft(b1);
        ntt2.dft(a2);
        ntt2.dft(b2);
        ntt3.dft(a3);
        ntt3.dft(b3);

        for (int i = 0; i < sz; ++i)
        {
            a0[i] *= b0[i];
            a1[i] *= b1[i];
            a2[i] *= b2[i];
            a3[i] *= b3[i];
        }

        ntt0.idft(a0);
        ntt1.idft(a1);
        ntt2.idft(a2);
        ntt3.idft(a3);
        std::vector<ModLL> ans(tot);

        for (int i(0); i < tot; ++i)
            ans[i] = crt(a0[i], a1[i], a2[i], a3[i]);

        return PolyBaseMFT4(ans);
    }
};
using PolyMFT = Poly<PolyBaseMFT4, ModLL>;
LL factorial(LL n, LL p)
{
    if (n >= p)
        return 0;
    if (n < 2)
        return 1;
    int s = __builtin_sqrtl(n);
    PolyMFT::setMod(p, s + 1);
    if (n > p - 1 - n)
    {
        auto ans = ModLL(factorial(p - 1 - n, p)).inv();
        return (p - n) & 1 ? -ans : ans;
    }
    std::vector<ModLL> h{1, s + 1};
    for (int bit(std::__lg(s) - 1), d(1); bit >= 0; --bit)
    {
        // Hiện tại h(i) = (i * s + 1) * (i * s + 1) ... (i * s + d)
        // Tính h(d+1), ..., h(2d)
        auto nh1 = PolyMFT::valToVal(h, ModLL(d + 1), d);
        // Tính h(d.inv(s)), ..., h(d.inv(s) + 2d)
        // Như vậy, nh2(i) = (i * s + d + 1) * (i * s + d + 2) ... (i * s + d * 2)
        auto nh2 = PolyMFT::valToVal(h, ModLL(s).inv() * ModLL(d), 2 * d + 1);
        // h giờ đây là h(0), h(1), ..., h(2d)
        h.insert(h.end(), nh1.begin(), nh1.end());
        // d --> d * 2
        d <<= 1;

        // Hiện tại h(i) = (i * s + 1) * (i * s + 2) ... (i * s + d/2)
        // Còn nh2(i) = (i * s + d/2 + 1) * (i * s + d/2 + 2) ... (i * s + d)
        for (int i(0); i <= d; ++i)
            h[i] *= nh2[i];
        // Tại đây h(i) = (i * s + 1) * (i * s + 1) ... (i * s + d)

        // Nếu bit hiện tại của s là 1
        if (s >> bit & 1)
        {
            d |= 1;
            LL tmp = d;

            // h[i] *= (d + i * s)
            for (int i(0); i < d; ++i, tmp += s)
                h[i] *= ModLL::raw(tmp);

            ModLL last(1), tj(1LL * s * d);

            // last = (d*s+1)(d*s+2)...(d*s+d)
            for (int i = 1; i <= d; ++i)
                ++tj, last *= tj;

            // Thêm biến last vào h
            h.emplace_back(last);
        }
    }
    ModLL ans = 1;

    for (int i(0); i < s; ++i)
        ans *= h[i];

    for (LL i(1LL * s * s + 1); i <= n; ++i)
        ans *= ModLL::raw(i);

    return ans;
}

main()
{
    std::cin.tie(NULL)->ios_base::sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--)
    {
        long long n, p;
        std::cin >> n >> p;
        std::cout << factorial(n, p) << '\n';
    }
}