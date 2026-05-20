"""
一键下载全部 16 篇论文 PDF
运行方式：python download.py
"""
import urllib.request
import os

os.makedirs(os.path.dirname(__file__) or ".", exist_ok=True)
os.chdir(os.path.dirname(__file__) or ".")

papers = [
    # (文件名, arXiv URL 或 备用 URL)
    ("01-Thakur等-MPICH集合通信优化-2005.pdf",
     "https://www.mpich.org/static/docs/papers/ijhpca-coll.pdf"),
    ("02-Dao等-FlashAttention-2022.pdf",
     "https://arxiv.org/pdf/2205.14135"),
    ("03-Dao-FlashAttention2-2023.pdf",
     "https://arxiv.org/pdf/2307.08691"),
    ("04-Shah等-FlashAttention3-2024.pdf",
     "https://arxiv.org/pdf/2407.08608"),
    ("05-Sergeev等-Horovod-2018.pdf",
     "https://arxiv.org/pdf/1802.05799"),
    ("06-Rajbhandari等-ZeRO-2019.pdf",
     "https://arxiv.org/pdf/1910.02054"),
    ("07-Shoeybi等-MegatronLM-TP-2019.pdf",
     "https://arxiv.org/pdf/1909.08053"),
    ("08-Narayanan等-MegatronLM-3D并行-2021.pdf",
     "https://arxiv.org/pdf/2104.04473"),
    ("09-Huang等-GPipe-流水线并行-2019.pdf",
     "https://arxiv.org/pdf/1811.06965"),
    ("10-Narayanan等-PipeDream-2019.pdf",
     "https://arxiv.org/pdf/1806.03377"),
    ("11-Kwon等-vLLM-PagedAttention-2023.pdf",
     "https://arxiv.org/pdf/2309.06180"),
    ("12-Lin等-AWQ-激活感知量化-2023.pdf",
     "https://arxiv.org/pdf/2306.00978"),
    ("13-Frantar等-GPTQ-2022.pdf",
     "https://arxiv.org/pdf/2210.17323"),
    ("14-Micikevicius等-FP8格式-2022.pdf",
     "https://arxiv.org/pdf/2209.05433"),
    ("15-Micikevicius等-混合精度训练-2017.pdf",
     "https://arxiv.org/pdf/1710.03740"),
    ("16-Fedus等-SwitchTransformers-MoE-2021.pdf",
     "https://arxiv.org/pdf/2101.03961"),
]

for fname, url in papers:
    if os.path.exists(fname):
        print(f"[跳过] {fname} 已存在")
        continue
    try:
        print(f"[下载] {fname} ...", end=" ", flush=True)
        urllib.request.urlretrieve(url, fname)
        size_kb = os.path.getsize(fname) // 1024
        print(f"OK ({size_kb} KB)")
    except Exception as e:
        print(f"失败: {e}")

print("\n全部完成。")
