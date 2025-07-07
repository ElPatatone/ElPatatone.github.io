---
layout: default
title: Projects 
---

<h1 class="page-title">{{ page.title }}</h1>

<ul>
  {% for project in site.projects %}
    <li class="post-item">
        <h1><a href="{{ project.url }}">{{ project.name }}</a></h1>
    </li>
  {% endfor %}
</ul>

